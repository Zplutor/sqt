#include <gtest/gtest.h>
#include <sqt/orm/column/column_like.h>
#include "orm_support_test.h"

using namespace orm_support;

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
        static_assert(sqt::ColumnLike<Table::IntColumnType>);

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
        static_assert(sqt::ColumnLike<Table::FloatColumnType>);

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
        static_assert(sqt::ColumnLike<Table::StringColumnType>);

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
        static_assert(sqt::ColumnLike<Table::NullableIntColumnType>);

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
        static_assert(sqt::ColumnLike<Table::NullableFloatColumnType>);

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
        static_assert(sqt::ColumnLike<Table::NullableStringColumnType>);

        constexpr auto column_name = table.NullableStringColumn.GetName();
        ASSERT_EQ(column_name, "NullableStringColumn");
        constexpr auto data_type = table.NullableStringColumn.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Text);
        constexpr bool is_nullable = table.NullableStringColumn.IsNullable();
        ASSERT_EQ(is_nullable, true);
    }
}


TEST(ORMSupportTest, NoColumnTable) {

    constexpr const auto& table = sqt::TableV<Entity0Column>;
    ASSERT_TRUE(table.GetColumns().empty());
    ASSERT_TRUE(table.GetAbstractColumns().empty());
}


TEST(ORMSupportTest, SingleColumnTable) {

    constexpr const auto& table = sqt::TableV<Entity1Column>;

    auto columns = table.GetColumns();
    ASSERT_EQ(columns.size(), 1);
    ASSERT_EQ(columns[0], &table.id);

    auto abstract_columns = table.GetAbstractColumns();
    ASSERT_EQ(abstract_columns.size(), 1);
    ASSERT_EQ(abstract_columns[0], &table.id);
}


TEST(ORMSupportTest, SingleColumnIndex) {

    using Table = sqt::TableT<Entity1Index>;

    static_assert(!std::is_copy_constructible_v<Table::IndexType_id0>);
    static_assert(!std::is_copy_assignable_v<Table::IndexType_id0>);
    static_assert(!std::is_move_constructible_v<Table::IndexType_id0>);
    static_assert(!std::is_move_assignable_v<Table::IndexType_id0>);

    constexpr auto& table = sqt::TableV<Entity1Index>;

    auto indexes = table.GetAbstractIndexes();
    ASSERT_EQ(indexes.size(), 1);
    ASSERT_EQ(indexes[0], &table.Index_id0);

    auto columns = table.Index_id0.GetAbstractColumns();
    ASSERT_EQ(columns.size(), 1);
    ASSERT_EQ(columns[0], &table.id0);
}


TEST(ORMSupportTest, TwoColumnIndex) {

    using Table = sqt::TableT<Entity2Index>;

    static_assert(!std::is_copy_constructible_v<Table::IndexType_id0id1>);
    static_assert(!std::is_copy_assignable_v<Table::IndexType_id0id1>);
    static_assert(!std::is_move_constructible_v<Table::IndexType_id0id1>);
    static_assert(!std::is_move_assignable_v<Table::IndexType_id0id1>);

    constexpr auto& table = sqt::TableV<Entity2Index>;

    auto indexes = table.GetAbstractIndexes();
    ASSERT_EQ(indexes.size(), 1);
    ASSERT_EQ(indexes[0], &table.Index_id0id1);

    auto columns = table.Index_id0id1.GetAbstractColumns();
    ASSERT_EQ(columns.size(), 2);
    ASSERT_EQ(columns[0], &table.id0);
    ASSERT_EQ(columns[1], &table.id1);
}


TEST(ORMSupportTest, MaxCountColumnIndex) {

    using Table = sqt::TableT<Entity8Index>;

    static_assert(!std::is_copy_constructible_v<Table::IndexType_id0id1id2id3id4id5id6id7>);
    static_assert(!std::is_copy_assignable_v<Table::IndexType_id0id1id2id3id4id5id6id7>);
    static_assert(!std::is_move_constructible_v<Table::IndexType_id0id1id2id3id4id5id6id7>);
    static_assert(!std::is_move_assignable_v<Table::IndexType_id0id1id2id3id4id5id6id7>);

    constexpr auto& table = sqt::TableV<Entity8Index>;

    auto indexes = table.GetAbstractIndexes();
    ASSERT_EQ(indexes.size(), 1);
    ASSERT_EQ(indexes[0], &table.Index_id0id1id2id3id4id5id6id7);

    auto columns = table.Index_id0id1id2id3id4id5id6id7.GetAbstractColumns();
    ASSERT_EQ(columns.size(), 8);
    ASSERT_EQ(columns[0], &table.id0);
    ASSERT_EQ(columns[1], &table.id1);
    ASSERT_EQ(columns[2], &table.id2);
    ASSERT_EQ(columns[3], &table.id3);
    ASSERT_EQ(columns[4], &table.id4);
    ASSERT_EQ(columns[5], &table.id5);
    ASSERT_EQ(columns[6], &table.id6);
    ASSERT_EQ(columns[7], &table.id7);
}


//Define table in different namespace.
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

SQT_REGISTER(orm, ScopedEntity)

TEST(ORMSupportTest, DifferentNamespace) {

    constexpr const auto& table = sqt::TableV<entity::ScopedEntity>;
    ASSERT_EQ(table.GetName(), "ScopedEntity");
}