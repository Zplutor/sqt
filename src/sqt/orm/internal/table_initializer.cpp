#include <sqt/orm/internal/table_initializer.h>
#include <format>
#include <sqt/foundation/transaction.h>
#include <sqt/orm/internal/utility.h>

namespace sqt::internal {

void TableInitializer::Initialize(const AbstractTable& table, Database& db) {

    Transaction transaction = db.BeginTransaction();

    auto table_info = db.GetTableInfo(table.GetName());
    if (!table_info) {
        CreateTable(table, db);
    }
    else {
        AlterTable(table, std::move(*table_info), db);
    }

    CreateIndexes(table, db);

    transaction.Commit();
}


void TableInitializer::CreateTable(const AbstractTable& table, Database& db) {

    const AbstractColumn* inline_pk_column{};
    auto pk = table.GetAbstractPrimaryKey();
    if (pk && pk->IsAutoInc()) {
        inline_pk_column = pk->GetAbstractColumns().front();
    }

    auto sql = std::format(
        "create table if not exists {} ({} {})",
        table.GetName(),
        GenerateColumnDefinitionsSQL(table.GetAbstractColumns(), inline_pk_column),
        inline_pk_column ?
            std::string{} :
            GeneratePrimaryKeyConstraintSQL(table.GetAbstractPrimaryKey()));

    db.ExecuteSQL(sql);
}


std::string TableInitializer::GenerateColumnDefinitionsSQL(
    std::span<const AbstractColumn* const> columns,
    const AbstractColumn* inline_pk_column) {

    std::string result;
    for (std::size_t index = 0; index < columns.size(); ++index) {
        if (index != 0) {
            result += ',';
        }
        auto column = columns[index];
        result += GenerateColumnSQL(*column, column == inline_pk_column);
    }
    return result;
}


std::string TableInitializer::GeneratePrimaryKeyConstraintSQL(
    const AbstractPrimaryKey* primary_key) {

    if (!primary_key) {
        return {};
    }

    return std::format(
        ", primary key ({})", 
        internal::JoinColumnNames(primary_key->GetAbstractColumns()));
}


void TableInitializer::AlterTable(
    const AbstractTable& table,
    TableInfo&& existent_table_info,
    Database& db) {

    std::sort(
        existent_table_info.columns.begin(), 
        existent_table_info.columns.end(),
        [](const auto& column1, const auto& column2) {
            return column1.name < column2.name;
        });

    std::vector<const AbstractColumn*> inexistent_columns;
    for (auto each_column : table.GetAbstractColumns()) {

        auto iterator = std::lower_bound(
            existent_table_info.columns.begin(),
            existent_table_info.columns.end(),
            each_column,
            [](const ColumnInfo& existent_column, const AbstractColumn* abstract_column) {
                return existent_column.name < abstract_column->GetName();
            });

        if (iterator == existent_table_info.columns.end() ||
            iterator->name != each_column->GetName()) {
            inexistent_columns.push_back(each_column);
        }
    }

    if (!inexistent_columns.empty()) {
        AddNewColumns(table, inexistent_columns, db);
    }
}


void TableInitializer::AddNewColumns(
    const AbstractTable& table,
    const std::vector<const AbstractColumn*>& columns,
    Database& db) {

    for (auto each_column : columns) {

        std::string sql = std::format(
            "alter table {} add column {}",
            table.GetName(),
            GenerateColumnSQL(*each_column, false));

        db.ExecuteSQL(sql);
    }
}


std::string TableInitializer::GenerateColumnSQL(
    const AbstractColumn& column,
    bool is_autoincrement) {

    std::string result = std::format(
        "{} {}",
        column.GetName(),
        DataTypeEnum::ToString(column.GetDataType()));

    if (!column.IsNullable()) {
        result += " not null";
    }

    if (auto default_value = column.GetDefaultValueSQLLiteral()) {
        result += " default ";
        result += *default_value;
    }

    if (is_autoincrement) {
        result += " primary key autoincrement";
    }

    return result;
}


void TableInitializer::CreateIndexes(const AbstractTable& table, Database& db) {

    for (auto each_index : table.GetAbstractIndexes()) {
        CreateIndex(table, *each_index, db);
    }
}


void TableInitializer::CreateIndex(
    const AbstractTable& table,
    const AbstractIndex& index,
    Database& db) {

    auto sql = std::format(
        "create {} index if not exists {} on {} ({})",
        index.IsUnique() ? "unique" : "",
        index.GetName(),
        table.GetName(),
        internal::JoinColumnNames(index.GetAbstractColumns()));

    db.ExecuteSQL(sql);
}

}