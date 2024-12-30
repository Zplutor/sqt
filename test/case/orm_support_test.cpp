#include <gtest/gtest.h>
#include "orm_support_test.h"

TEST(ORMSupportTest, TableDefinition) {

    using Table = __sqt_table_Entity::TableType;

    static_assert(!std::is_copy_constructible_v<Table>);
    static_assert(!std::is_copy_assignable_v<Table>);
    static_assert(!std::is_move_constructible_v<Table>);
    static_assert(!std::is_move_assignable_v<Table>);

    //GetInstance should be constexpr
    constexpr const auto& table = Table::GetInstance();

    //GetName should be constexpr
    constexpr auto table_name = table.GetName();
    ASSERT_EQ(table_name, "Entity");

    //GetColumns should be constexpr
    constexpr auto columns = table.GetColumns();
    ASSERT_EQ(columns.size(), 2);
    ASSERT_EQ(columns[0], &table.IntColumn);
    ASSERT_EQ(columns[1], &table.StringColumn);

    auto abstract_columns = table.GetAbstractColumns();
    ASSERT_EQ(abstract_columns.size(), 2);
    ASSERT_EQ(abstract_columns[0], &table.IntColumn);
    ASSERT_EQ(abstract_columns[1], &table.StringColumn);

    //Check columns
    {
        static_assert(!std::is_copy_constructible_v<Table::IntColumnType>);
        static_assert(!std::is_copy_assignable_v<Table::IntColumnType>);
        static_assert(!std::is_move_constructible_v<Table::IntColumnType>);
        static_assert(!std::is_move_assignable_v<Table::IntColumnType>);

        constexpr auto column_name = table.IntColumn.GetName();
        ASSERT_EQ(column_name, "IntColumn");
    }

    {
        static_assert(!std::is_copy_constructible_v<Table::StringColumnType>);
        static_assert(!std::is_copy_assignable_v<Table::StringColumnType>);
        static_assert(!std::is_move_constructible_v<Table::StringColumnType>);
        static_assert(!std::is_move_assignable_v<Table::StringColumnType>);

        constexpr auto column_name = table.StringColumn.GetName();
        ASSERT_EQ(column_name, "StringColumn");
    }
}


TEST(ORMSupportTest, NoColumn) {

    const auto& table = __sqt_table_Entity0Column::TableType::GetInstance();
    ASSERT_TRUE(table.GetColumns().empty());
    ASSERT_TRUE(table.GetAbstractColumns().empty());
}


TEST(ORMSupportTest, SingleColumn) {

    const auto& table = __sqt_table_Entity1Column::TableType::GetInstance();

    auto columns = table.GetColumns();
    ASSERT_EQ(columns.size(), 1);
    ASSERT_EQ(columns[0], &table.id);

    auto abstract_columns = table.GetAbstractColumns();
    ASSERT_EQ(abstract_columns.size(), 1);
    ASSERT_EQ(abstract_columns[0], &table.id);
}