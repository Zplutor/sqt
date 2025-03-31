#include <concepts>
#include <gtest/gtest.h>
#include <sqt/orm/table_definition.h>
#include <sqt/orm/table_mapping.h>

namespace table_def_test {
struct NoColumnEntity {};
SQT_TABLE_BEGIN(NoColumnEntity, NoColumnEntity)
SQT_TABLE_END

struct OneColumnEntity {
    int id{};
};
SQT_TABLE_BEGIN(OneColumnEntity, OneColumnEntity)
SQT_COLUMN_FIELD(id, id)
SQT_TABLE_END

struct TwoColumnEntity {
    int id0{};
    int id1{};
};
SQT_TABLE_BEGIN(TwoColumnEntity, TwoColumnEntity)
SQT_COLUMN_FIELD(id0, id0)
SQT_COLUMN_FIELD(id1, id1)
SQT_TABLE_END
}

SQT_REGISTER(table_def_test::NoColumnEntity)
SQT_REGISTER(table_def_test::OneColumnEntity)
SQT_REGISTER(table_def_test::TwoColumnEntity)


TEST(TableDefinitionTest, TableBasicInterface) {

    using Table = sqt::TableType<table_def_test::NoColumnEntity>;

    static_assert(!std::copyable<Table>);
    static_assert(!std::movable<Table>);

    static_assert(std::is_same_v<Table::EntityType, table_def_test::NoColumnEntity>);

    constexpr auto& table = Table::GetInstance();
    ASSERT_EQ(table.GetName(), "NoColumnEntity");
}


TEST(TableDefinitionTest, GetColumns) {

    //No Column
    {
        using Table = sqt::TableType<table_def_test::NoColumnEntity>;
        constexpr sqt::ColumnsView<table_def_test::NoColumnEntity> columns = Table::GetColumns();
        ASSERT_EQ(columns.size(), 0);
    }

    //One Column
    {
        using Table = sqt::TableType<table_def_test::OneColumnEntity>;
        constexpr sqt::ColumnsView<table_def_test::OneColumnEntity> columns = Table::GetColumns();
        ASSERT_EQ(columns.size(), 1);
        ASSERT_EQ(columns[0], &Table::GetInstance().id);
    }

    //Two columns
    {
        using Table = sqt::TableType<table_def_test::TwoColumnEntity>;
        constexpr sqt::ColumnsView<table_def_test::TwoColumnEntity> columns = Table::GetColumns();
        ASSERT_EQ(columns.size(), 2);
        ASSERT_EQ(columns[0], &Table::GetInstance().id0);
        ASSERT_EQ(columns[1], &Table::GetInstance().id1);
    }
}


TEST(TableDefinitionTest, GetAbstractColumns) {

    //No Column
    {
        constexpr auto& table = sqt::Table<table_def_test::NoColumnEntity>;
        auto abstract_columns = table.GetAbstractColumns();
        ASSERT_EQ(abstract_columns.size(), 0);
    }

    //One Column
    {
        constexpr auto& table = sqt::Table<table_def_test::OneColumnEntity>;
        auto abstract_columns = table.GetAbstractColumns();
        ASSERT_EQ(abstract_columns.size(), 1);
        ASSERT_EQ(abstract_columns[0], &table.id);
    }

    //Two columns
    {
        constexpr auto& table = sqt::Table<table_def_test::TwoColumnEntity>;
        auto abstract_columns = table.GetAbstractColumns();
        ASSERT_EQ(abstract_columns.size(), 2);
        ASSERT_EQ(abstract_columns[0], &table.id0);
        ASSERT_EQ(abstract_columns[1], &table.id1);
    }
}


namespace table_def_test {
struct NoPKEntity {
    int id{};
};
SQT_TABLE_BEGIN(NoPKEntity, NoPKEntity)
SQT_COLUMN_FIELD(id, id)
SQT_TABLE_END

struct AllPKEntity {
    int id0{};
    int id1{};
};
SQT_TABLE_BEGIN(AllPKEntity, AllPKEntity)
SQT_COLUMN_FIELD(id0, id0)
SQT_COLUMN_FIELD(id1, id1)
SQT_PRIMARY_KEY(id0, id1)
SQT_TABLE_END

struct PartialPKEntity {
    int id0{};
    int id1{};
};
SQT_TABLE_BEGIN(PartialPKEntity, PartialPKEntity)
SQT_COLUMN_FIELD(id0, id0)
SQT_COLUMN_FIELD(id1, id1)
SQT_PRIMARY_KEY(id0)
SQT_TABLE_END
}

SQT_REGISTER(table_def_test::NoPKEntity)
SQT_REGISTER(table_def_test::AllPKEntity)
SQT_REGISTER(table_def_test::PartialPKEntity)

TEST(TableDefinitionTest, GetPrimaryKeyColumns) {

    //No primary key
    {
        using Table = sqt::TableType<table_def_test::NoPKEntity>;
        constexpr sqt::ColumnsView<table_def_test::NoPKEntity> columns = 
            Table::GetPrimaryKeyColumns();
        ASSERT_EQ(columns.size(), 0);
    }

    //All primary key
    {
        using Table = sqt::TableType<table_def_test::AllPKEntity>;
        constexpr sqt::ColumnsView<table_def_test::AllPKEntity> columns =
            Table::GetPrimaryKeyColumns();
        ASSERT_EQ(columns.size(), 2);
        ASSERT_EQ(columns[0], &Table::GetInstance().id0);
        ASSERT_EQ(columns[1], &Table::GetInstance().id1);
    }

    //Partial primary key
    {
        using Table = sqt::TableType<table_def_test::PartialPKEntity>;
        constexpr sqt::ColumnsView<table_def_test::PartialPKEntity> columns =
            Table::GetPrimaryKeyColumns();
        ASSERT_EQ(columns.size(), 1);
        ASSERT_EQ(columns[0], &Table::GetInstance().id0);
    }
}


TEST(TableDefinitionTest, GetNonPrimaryKeyColumns) {

    //No primary key
    {
        using Table = sqt::TableType<table_def_test::NoPKEntity>;
        constexpr sqt::ColumnsView<table_def_test::NoPKEntity> columns =
            Table::GetNonPrimaryKeyColumns();
        ASSERT_EQ(columns.size(), 1);
        ASSERT_EQ(columns[0], &Table::GetInstance().id);
    }

    //All primary key
    {
        using Table = sqt::TableType<table_def_test::AllPKEntity>;
        constexpr sqt::ColumnsView<table_def_test::AllPKEntity> columns =
            Table::GetNonPrimaryKeyColumns();
        ASSERT_EQ(columns.size(), 0);
    }

    //Partial primary key
    {
        using Table = sqt::TableType<table_def_test::PartialPKEntity>;
        constexpr sqt::ColumnsView<table_def_test::PartialPKEntity> columns =
            Table::GetNonPrimaryKeyColumns();
        ASSERT_EQ(columns.size(), 1);
        ASSERT_EQ(columns[0], &Table::GetInstance().id1);
    }
}


TEST(TableDefinitionTest, GetAbstractPrimaryKey) {

    //No primary key
    {
        constexpr auto& table = sqt::Table<table_def_test::NoPKEntity>;
        auto abstract_pk = table.GetAbstractPrimaryKey();
        ASSERT_EQ(abstract_pk, nullptr);
    }

    //All primary key
    {
        constexpr auto& table = sqt::Table<table_def_test::AllPKEntity>;
        auto abstract_pk = table.GetAbstractPrimaryKey();
        ASSERT_EQ(abstract_pk, &table.PrimaryKey);
    }

    //Partial primary key
    {
        constexpr auto& table = sqt::Table<table_def_test::PartialPKEntity>;
        auto abstract_pk = table.GetAbstractPrimaryKey();
        ASSERT_EQ(abstract_pk, &table.PrimaryKey);
    }
}


namespace table_def_test {
struct NoIndexEntity {
    int id0{};
    int id1{};
};
SQT_TABLE_BEGIN(NoIndexEntity, NoIndexEntity)
SQT_COLUMN_FIELD(id0, id0)
SQT_COLUMN_FIELD(id1, id1)
SQT_TABLE_END

struct IndexEntity {
    int id0{};
    int id1{};
};
SQT_TABLE_BEGIN(IndexEntity, IndexEntity)
SQT_COLUMN_FIELD(id0, id0)
SQT_COLUMN_FIELD(id1, id1)
SQT_INDEX(id0)
SQT_TABLE_END
}

SQT_REGISTER(table_def_test::NoIndexEntity)
SQT_REGISTER(table_def_test::IndexEntity)

TEST(TableDefinitionTest, GetAbstractIndexes) {

    //No index
    {
        constexpr auto& table = sqt::Table<table_def_test::NoIndexEntity>;
        auto abstract_indexes = table.GetAbstractIndexes();
        ASSERT_EQ(abstract_indexes.size(), 0);
    }

    //Index
    {
        constexpr auto& table = sqt::Table<table_def_test::IndexEntity>;
        auto abstract_indexes = table.GetAbstractIndexes();
        ASSERT_EQ(abstract_indexes.size(), 1);
        ASSERT_EQ(abstract_indexes[0], &table.Index_id0);
    }
}