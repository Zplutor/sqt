#include <gtest/gtest.h>
#include "orm_support_test.h"

TEST(ORMSupportTest, TableDefinition) {

    using Table = sqt::TableT<Entity>;

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
    ASSERT_EQ(columns.size(), 6);
    ASSERT_EQ(columns[0], &table.IntColumn);
    ASSERT_EQ(columns[1], &table.FloatColumn);
    ASSERT_EQ(columns[2], &table.StringColumn);
    ASSERT_EQ(columns[3], &table.NullableIntColumn);
    ASSERT_EQ(columns[4], &table.NullableFloatColumn);
    ASSERT_EQ(columns[5], &table.NullableStringColumn);

    auto abstract_columns = table.GetAbstractColumns();
    ASSERT_EQ(abstract_columns.size(), 6);
    ASSERT_EQ(abstract_columns[0], &table.IntColumn);
    ASSERT_EQ(abstract_columns[1], &table.FloatColumn);
    ASSERT_EQ(abstract_columns[2], &table.StringColumn);
    ASSERT_EQ(abstract_columns[3], &table.NullableIntColumn);
    ASSERT_EQ(abstract_columns[4], &table.NullableFloatColumn);
    ASSERT_EQ(abstract_columns[5], &table.NullableStringColumn);

    //Check columns
    {
        static_assert(!std::is_copy_constructible_v<Table::IntColumnType>);
        static_assert(!std::is_copy_assignable_v<Table::IntColumnType>);
        static_assert(!std::is_move_constructible_v<Table::IntColumnType>);
        static_assert(!std::is_move_assignable_v<Table::IntColumnType>);

        constexpr auto column_name = table.IntColumn.GetName();
        ASSERT_EQ(column_name, "IntColumn");
        constexpr auto data_type = table.IntColumn.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = table.IntColumn.IsNullable();
        ASSERT_EQ(is_nullable, false);
    }

    {
        static_assert(!std::is_copy_constructible_v<Table::FloatColumnType>);
        static_assert(!std::is_copy_assignable_v<Table::FloatColumnType>);
        static_assert(!std::is_move_constructible_v<Table::FloatColumnType>);
        static_assert(!std::is_move_assignable_v<Table::FloatColumnType>);

        constexpr auto column_name = table.FloatColumn.GetName();
        ASSERT_EQ(column_name, "FloatColumn");
        constexpr auto data_type = table.FloatColumn.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Float);
        constexpr bool is_nullable = table.FloatColumn.IsNullable();
        ASSERT_EQ(is_nullable, false);
    }

    {
        static_assert(!std::is_copy_constructible_v<Table::StringColumnType>);
        static_assert(!std::is_copy_assignable_v<Table::StringColumnType>);
        static_assert(!std::is_move_constructible_v<Table::StringColumnType>);
        static_assert(!std::is_move_assignable_v<Table::StringColumnType>);

        constexpr auto column_name = table.StringColumn.GetName();
        ASSERT_EQ(column_name, "StringColumn");
        constexpr auto data_type = table.StringColumn.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Text);
        constexpr bool is_nullable = table.StringColumn.IsNullable();
        ASSERT_EQ(is_nullable, false);
    }

    {
        static_assert(!std::is_copy_constructible_v<Table::NullableIntColumnType>);
        static_assert(!std::is_copy_assignable_v<Table::NullableIntColumnType>);
        static_assert(!std::is_move_constructible_v<Table::NullableIntColumnType>);
        static_assert(!std::is_move_assignable_v<Table::NullableIntColumnType>);

        constexpr auto column_name = table.NullableIntColumn.GetName();
        ASSERT_EQ(column_name, "NullableIntColumn");
        constexpr auto data_type = table.NullableIntColumn.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = table.NullableIntColumn.IsNullable();
        ASSERT_EQ(is_nullable, true);
    }

    {
        static_assert(!std::is_copy_constructible_v<Table::NullableFloatColumnType>);
        static_assert(!std::is_copy_assignable_v<Table::NullableFloatColumnType>);
        static_assert(!std::is_move_constructible_v<Table::NullableFloatColumnType>);
        static_assert(!std::is_move_assignable_v<Table::NullableFloatColumnType>);

        constexpr auto column_name = table.NullableFloatColumn.GetName();
        ASSERT_EQ(column_name, "NullableFloatColumn");
        constexpr auto data_type = table.NullableFloatColumn.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Float);
        constexpr bool is_nullable = table.NullableFloatColumn.IsNullable();
        ASSERT_EQ(is_nullable, true);
    }

    {
        static_assert(!std::is_copy_constructible_v<Table::NullableStringColumnType>);
        static_assert(!std::is_copy_assignable_v<Table::NullableStringColumnType>);
        static_assert(!std::is_move_constructible_v<Table::NullableStringColumnType>);
        static_assert(!std::is_move_assignable_v<Table::NullableStringColumnType>);

        constexpr auto column_name = table.NullableStringColumn.GetName();
        ASSERT_EQ(column_name, "NullableStringColumn");
        constexpr auto data_type = table.NullableStringColumn.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Text);
        constexpr bool is_nullable = table.NullableStringColumn.IsNullable();
        ASSERT_EQ(is_nullable, true);
    }
}


TEST(ORMSupportTest, NoColumn) {

    constexpr const auto& table = sqt::TableV<Entity0Column>;
    ASSERT_TRUE(table.GetColumns().empty());
    ASSERT_TRUE(table.GetAbstractColumns().empty());
}


TEST(ORMSupportTest, SingleColumn) {

    constexpr const auto& table = sqt::TableV<Entity1Column>;

    auto columns = table.GetColumns();
    ASSERT_EQ(columns.size(), 1);
    ASSERT_EQ(columns[0], &table.id);

    auto abstract_columns = table.GetAbstractColumns();
    ASSERT_EQ(abstract_columns.size(), 1);
    ASSERT_EQ(abstract_columns[0], &table.id);
}


//Define ORM in different namespace.
namespace entity {
struct ScopedEntity {
    int id{};
};
}

namespace orm {
SQT_TABLE_BEGIN(ScopedEntity, entity::ScopedEntity)
SQT_COLUMN(ID, id)
SQT_TABLE_END
}

SQT_MAP(orm, ScopedEntity)

TEST(ORMSupportTest, DifferentNamespace) {

    constexpr const auto& table = sqt::TableV<entity::ScopedEntity>;
    ASSERT_EQ(table.GetName(), "ScopedEntity");
}