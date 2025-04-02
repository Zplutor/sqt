#include <concepts>
#include <gtest/gtest.h>
#include <sqt/orm/table_definition.h>
#include <sqt/orm/table_mapping.h>

namespace pk_def_test {
struct OneColumnPK {
    int id0{};
    int id1{};
};
SQT_TABLE_BEGIN(OneColumnPK, OneColumnPK)
SQT_COLUMN_FIELD(id0, id0)
SQT_COLUMN_FIELD(id1, id0)
SQT_PRIMARY_KEY(id0)
SQT_TABLE_END

struct TwoColumnPK {
    int id0{};
    int id1{};
};
SQT_TABLE_BEGIN(TwoColumnPK, TwoColumnPK)
SQT_COLUMN_FIELD(id0, id0)
SQT_COLUMN_FIELD(id1, id0)
SQT_PRIMARY_KEY(id0, id1)
SQT_TABLE_END

struct AutoIncPK {
    int id{};
    std::string name;
};
SQT_TABLE_BEGIN(AutoIncPK, AutoIncPK)
SQT_COLUMN_FIELD(id, id)
SQT_COLUMN_FIELD(name, name)
SQT_PRIMARY_KEY_AUTO_INC(id)
SQT_TABLE_END
}

SQT_REGISTER(pk_def_test::OneColumnPK)
SQT_REGISTER(pk_def_test::TwoColumnPK)
SQT_REGISTER(pk_def_test::AutoIncPK)


TEST(PrimaryKeyDefinitionTest, NonCopyableMovable) {

    // One column PK
    {
        using TableType = sqt::TableType<pk_def_test::OneColumnPK>;
        static_assert(!std::copyable<TableType::PrimaryKeyType>);
        static_assert(!std::movable<TableType::PrimaryKeyType>);
    }

    // Two column PK
    {
        using TableType = sqt::TableType<pk_def_test::TwoColumnPK>;
        static_assert(!std::copyable<TableType::PrimaryKeyType>);
        static_assert(!std::movable<TableType::PrimaryKeyType>);
    }

    // Auto inc PK
    {
        using TableType = sqt::TableType<pk_def_test::AutoIncPK>;
        static_assert(!std::copyable<TableType::PrimaryKeyType>);
        static_assert(!std::movable<TableType::PrimaryKeyType>);
    }
}


TEST(PrimaryKeyDefinitionTest, IsAutoInc) {

    // One column PK
    {
        constexpr auto& table = sqt::Table<pk_def_test::OneColumnPK>;
        constexpr bool auto_inc = table.PrimaryKey.IsAutoInc();
        ASSERT_FALSE(auto_inc);
    }

    // Two column PK
    {
        constexpr auto& table = sqt::Table<pk_def_test::TwoColumnPK>;
        constexpr bool auto_inc = table.PrimaryKey.IsAutoInc();
        ASSERT_FALSE(auto_inc);
    }

    // Auto inc PK
    {
        constexpr auto& table = sqt::Table<pk_def_test::AutoIncPK>;
        constexpr bool auto_inc = table.PrimaryKey.IsAutoInc();
        ASSERT_TRUE(auto_inc);
    }
}


TEST(PrimaryKeyDefinitionTest, GetAbstractColumns) {

    // One column PK
    {
        constexpr auto& table = sqt::Table<pk_def_test::OneColumnPK>;
        auto columns = table.PrimaryKey.GetAbstractColumns();
        ASSERT_EQ(columns.size(), 1);
        ASSERT_EQ(columns[0], &table.id0);
    }

    // Two column PK
    {
        constexpr auto& table = sqt::Table<pk_def_test::TwoColumnPK>;
        auto columns = table.PrimaryKey.GetAbstractColumns();
        ASSERT_EQ(columns.size(), 2);
        ASSERT_EQ(columns[0], &table.id0);
        ASSERT_EQ(columns[1], &table.id1);
    }

    // Auto inc PK
    {
        constexpr auto& table = sqt::Table<pk_def_test::AutoIncPK>;
        auto columns = table.PrimaryKey.GetAbstractColumns();
        ASSERT_EQ(columns.size(), 1);
        ASSERT_EQ(columns[0], &table.id);
    }
}