#include <sqt/core/database.h>
#include <format>
#include <sqt/core/sql_error.h>

namespace sqt {

Database Database::Open(const std::filesystem::path& path) {

    sqlite3* handle{};

    auto utf8_path = path.u8string();
    int error_code = sqlite3_open_v2(
        reinterpret_cast<const char*>(utf8_path.c_str()), 
        &handle,
        SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, 
        nullptr);

    Database database{ handle };
    SQT_THROW_IF_SQL_ERROR(error_code, handle);
    return database;
}


Database::Database(sqlite3* handle) noexcept : handle_(handle) {

}


Database::~Database() {
    Reset();
}


Database::Database(Database&& other) noexcept : handle_(other.handle_) {
    other.handle_ = nullptr;
}


Database& Database::operator=(Database&& other) noexcept {

    if (this != &other) {
        Reset();
        handle_ = other.handle_;
        other.handle_ = nullptr;
    }
    return *this;
}


void Database::Reset() noexcept {

    if (handle_) {
        sqlite3_close_v2(handle_);
        handle_ = nullptr;
    }
}


void Database::ExecuteSQL(std::string_view sql) {

    auto statement = PrepareStatement(sql);
    statement.Step();
}


Statement Database::PrepareStatement(std::string_view sql) {

    sqlite3_stmt* statement_handle{};
    int error_code = sqlite3_prepare_v2(
        handle_, 
        sql.data(),
        static_cast<int>(sql.length()),
        &statement_handle, 
        nullptr);

    SQT_THROW_IF_SQL_ERROR(error_code, handle_);

    return Statement{ handle_, statement_handle };
}


std::int64_t Database::LastInsertRowID() const {
    return sqlite3_last_insert_rowid(handle_);
}


std::size_t Database::LastChanges() const {
    return sqlite3_changes(handle_);
}


std::optional<TableInfo> Database::GetTableInfo(std::string_view table_name) {

    auto sql = std::format("pragma table_info({})", table_name);
    auto statement = PrepareStatement(sql);

    TableInfo table_info;
    while (statement.Step()) {

        ColumnInfo column_info;
        column_info.name = statement.GetColumnText(1);
        column_info.data_type = DataTypeTraits::FromString(statement.GetColumnText(2));
        bool is_not_null = statement.GetColumnInt(3) != 0;
        column_info.is_nullable = !is_not_null;
        column_info.is_primary_key = statement.GetColumnInt(5) != 0;

        table_info.columns.push_back(std::move(column_info));
    }

    if (table_info.columns.empty()) {
        return std::nullopt;
    }

    return table_info;
}


std::optional<IndexInfo> Database::GetIndexInfo(std::string_view index_name) {

    auto sql = std::format("pragma index_info({})", index_name);
    auto statement = PrepareStatement(sql);

    IndexInfo result;
    while (statement.Step()) {

        std::string column_name{ statement.GetColumnText(2) };
        result.columns.push_back(std::move(column_name));
    }

    if (result.columns.empty()) {
        return std::nullopt;
    }

    return result;
}

}