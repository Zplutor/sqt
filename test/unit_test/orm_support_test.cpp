#include <gtest/gtest.h>
#include <sqt/orm/table/column/column_type.h>
#include "orm_support_test.h"

using namespace orm_support;

TEST(ORMSupportTest, TableDefinition) {

    using Table = sqt::TableType<Entity>;

    static_assert(!std::is_copy_constructible_v<Table>);
    static_assert(!std::is_copy_assignable_v<Table>);
    static_assert(!std::is_move_constructible_v<Table>);
    static_assert(!std::is_move_assignable_v<Table>);

    //GetInstance should be constexpr
    constexpr const auto& table = Table::GetInstance();

    //GetColumns should be constexpr
    constexpr auto columns = Table::GetColumns();
    ASSERT_EQ(columns.size(), 6);
    ASSERT_EQ(columns[0], &table.IntColumn);
    ASSERT_EQ(columns[1], &table.FloatColumn);
    ASSERT_EQ(columns[2], &table.StringColumn);
    ASSERT_EQ(columns[3], &table.NullableIntColumn);
    ASSERT_EQ(columns[4], &table.NullableFloatColumn);
    ASSERT_EQ(columns[5], &table.NullableStringColumn);

    constexpr auto pk_columns = Table::GetPrimaryKeyColumns();
    ASSERT_EQ(pk_columns.size(), 0);

    constexpr auto non_pk_columns = Table::GetNonPrimaryKeyColumns();
    ASSERT_EQ(non_pk_columns.size(), 6);
    ASSERT_EQ(non_pk_columns[0], &table.IntColumn);
    ASSERT_EQ(non_pk_columns[1], &table.FloatColumn);
    ASSERT_EQ(non_pk_columns[2], &table.StringColumn);
    ASSERT_EQ(non_pk_columns[3], &table.NullableIntColumn);
    ASSERT_EQ(non_pk_columns[4], &table.NullableFloatColumn);
    ASSERT_EQ(non_pk_columns[5], &table.NullableStringColumn);

    //GetAbstractPrimaryKey should be constexpr
    constexpr auto primary_key = table.GetAbstractPrimaryKey();
    ASSERT_EQ(primary_key, nullptr);

    //GetName should be constexpr
    constexpr auto table_name = table.GetName();
    ASSERT_EQ(table_name, "Entity");

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
        static_assert(sqt::ColumnType<Table::IntColumnType>);

        ASSERT_EQ(Table::IntColumnType::Name, "IntColumn");
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
        static_assert(sqt::ColumnType<Table::FloatColumnType>);

        ASSERT_EQ(Table::FloatColumnType::Name, "FloatColumn");
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
        static_assert(sqt::ColumnType<Table::StringColumnType>);

        ASSERT_EQ(Table::StringColumnType::Name, "StringColumn");
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
        static_assert(sqt::ColumnType<Table::NullableIntColumnType>);

        ASSERT_EQ(Table::NullableIntColumnType::Name, "NullableIntColumn");
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
        static_assert(sqt::ColumnType<Table::NullableFloatColumnType>);

        ASSERT_EQ(Table::NullableFloatColumnType::Name, "NullableFloatColumn");
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
        static_assert(sqt::ColumnType<Table::NullableStringColumnType>);

        ASSERT_EQ(Table::NullableStringColumnType::Name, "NullableStringColumn");
        constexpr auto column_name = table.NullableStringColumn.GetName();
        ASSERT_EQ(column_name, "NullableStringColumn");
        constexpr auto data_type = table.NullableStringColumn.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Text);
        constexpr bool is_nullable = table.NullableStringColumn.IsNullable();
        ASSERT_EQ(is_nullable, true);
    }
}


TEST(ORMSupportTest, NoColumnTable) {

    constexpr const auto& table = sqt::Table<Entity0Column>;
    ASSERT_TRUE(table.GetColumns().empty());
    ASSERT_TRUE(table.GetAbstractColumns().empty());
}


TEST(ORMSupportTest, SingleColumnTable) {

    constexpr const auto& table = sqt::Table<Entity1Column>;

    auto columns = table.GetColumns();
    ASSERT_EQ(columns.size(), 1);
    ASSERT_EQ(columns[0], &table.id);

    auto abstract_columns = table.GetAbstractColumns();
    ASSERT_EQ(abstract_columns.size(), 1);
    ASSERT_EQ(abstract_columns[0], &table.id);
}


TEST(ORMSupportTest, SingleColumnPrimaryKey) {

    using Table = sqt::TableType<EntityPK1>;
    static_assert(!std::is_copy_constructible_v<Table::PrimaryKeyType>);
    static_assert(!std::is_copy_assignable_v<Table::PrimaryKeyType>);
    static_assert(!std::is_move_constructible_v<Table::PrimaryKeyType>);
    static_assert(!std::is_move_assignable_v<Table::PrimaryKeyType>);

    constexpr auto& table = sqt::Table<EntityPK1>;

    constexpr auto abstract_pk = table.GetAbstractPrimaryKey();
    ASSERT_EQ(abstract_pk, &table.PrimaryKey);

    constexpr bool auto_inc = table.PrimaryKey.IsAutoInc();
    ASSERT_FALSE(auto_inc);

    constexpr auto table_pk_columns = Table::GetPrimaryKeyColumns();
    ASSERT_EQ(table_pk_columns.size(), 1);
    ASSERT_EQ(table_pk_columns[0], &table.id0);

    constexpr auto table_non_pk_columns = Table::GetNonPrimaryKeyColumns();
    ASSERT_EQ(table_non_pk_columns.size(), 1);
    ASSERT_EQ(table_non_pk_columns[0], &table.id1);

    constexpr auto pk_columns = table.PrimaryKey.GetColumns();
    ASSERT_EQ(pk_columns.size(), 1);
    ASSERT_EQ(pk_columns[0], &table.id0);

    auto abstract_columns = table.PrimaryKey.GetAbstractColumns();
    ASSERT_EQ(abstract_columns.size(), 1);
    ASSERT_EQ(abstract_columns[0], &table.id0);
}


TEST(ORMSupportTest, TwoColumnPrimaryKey) {

    using Table = sqt::TableType<EntityPK2>;
    static_assert(!std::is_copy_constructible_v<Table::PrimaryKeyType>);
    static_assert(!std::is_copy_assignable_v<Table::PrimaryKeyType>);
    static_assert(!std::is_move_constructible_v<Table::PrimaryKeyType>);
    static_assert(!std::is_move_assignable_v<Table::PrimaryKeyType>);

    constexpr auto& table = sqt::Table<EntityPK2>;

    constexpr auto abstract_pk = table.GetAbstractPrimaryKey();
    ASSERT_EQ(abstract_pk, &table.PrimaryKey);

    constexpr bool auto_inc = table.PrimaryKey.IsAutoInc();
    ASSERT_FALSE(auto_inc);

    constexpr auto table_pk_columns = Table::GetPrimaryKeyColumns();
    ASSERT_EQ(table_pk_columns.size(), 2);
    ASSERT_EQ(table_pk_columns[0], &table.id0);
    ASSERT_EQ(table_pk_columns[1], &table.id1);

    constexpr auto table_non_pk_columns = Table::GetNonPrimaryKeyColumns();
    ASSERT_EQ(table_non_pk_columns.size(), 1);
    ASSERT_EQ(table_non_pk_columns[0], &table.id2);

    constexpr auto pk_columns = table.PrimaryKey.GetColumns();
    ASSERT_EQ(pk_columns.size(), 2);
    ASSERT_EQ(pk_columns[0], &table.id0);
    ASSERT_EQ(pk_columns[1], &table.id1);

    auto abstract_columns = table.PrimaryKey.GetAbstractColumns();
    ASSERT_EQ(abstract_columns.size(), 2);
    ASSERT_EQ(abstract_columns[0], &table.id0);
    ASSERT_EQ(abstract_columns[1], &table.id1);
}


TEST(ORMSupportTest, AutoIncrementPrimaryKey) {

    constexpr auto& table = sqt::Table<EntityPKAutoInc>;
    constexpr bool auto_inc = table.PrimaryKey.IsAutoInc();
    ASSERT_TRUE(auto_inc);

    auto columns = table.PrimaryKey.GetAbstractColumns();
    ASSERT_EQ(columns.size(), 1);
    ASSERT_EQ(columns[0]->GetName(), "id");
}


TEST(ORMSupportTest, SingleColumnIndex) {

    using Table = sqt::TableType<Entity1Index>;

    static_assert(!std::is_copy_constructible_v<Table::IndexType_id0>);
    static_assert(!std::is_copy_assignable_v<Table::IndexType_id0>);
    static_assert(!std::is_move_constructible_v<Table::IndexType_id0>);
    static_assert(!std::is_move_assignable_v<Table::IndexType_id0>);

    constexpr auto& table = sqt::Table<Entity1Index>;

    auto indexes = table.GetAbstractIndexes();
    ASSERT_EQ(indexes.size(), 1);
    ASSERT_EQ(indexes[0], &table.Index_id0);

    auto index_name = table.Index_id0.GetName();
    ASSERT_EQ(index_name, "Entity1Index_Index_id0");

    auto columns = table.Index_id0.GetAbstractColumns();
    ASSERT_EQ(columns.size(), 1);
    ASSERT_EQ(columns[0], &table.id0);

    constexpr bool is_unique = table.Index_id0.IsUnique();
    ASSERT_FALSE(is_unique);
}


TEST(ORMSupportTest, TwoColumnIndex) {

    using Table = sqt::TableType<Entity2Index>;

    static_assert(!std::is_copy_constructible_v<Table::IndexType_id0id1>);
    static_assert(!std::is_copy_assignable_v<Table::IndexType_id0id1>);
    static_assert(!std::is_move_constructible_v<Table::IndexType_id0id1>);
    static_assert(!std::is_move_assignable_v<Table::IndexType_id0id1>);

    constexpr auto& table = sqt::Table<Entity2Index>;

    auto indexes = table.GetAbstractIndexes();
    ASSERT_EQ(indexes.size(), 1);
    ASSERT_EQ(indexes[0], &table.Index_id0id1);

    auto index_name = table.Index_id0id1.GetName();
    ASSERT_EQ(index_name, "Entity2Index_Index_id0id1");

    auto columns = table.Index_id0id1.GetAbstractColumns();
    ASSERT_EQ(columns.size(), 2);
    ASSERT_EQ(columns[0], &table.id0);
    ASSERT_EQ(columns[1], &table.id1);

    constexpr bool is_unique = table.Index_id0id1.IsUnique();
    ASSERT_FALSE(is_unique);
}


TEST(ORMSupportTest, MaxCountColumnIndex) {

    using Table = sqt::TableType<Entity8Index>;

    static_assert(!std::is_copy_constructible_v<Table::IndexType_id0id1id2id3id4id5id6id7>);
    static_assert(!std::is_copy_assignable_v<Table::IndexType_id0id1id2id3id4id5id6id7>);
    static_assert(!std::is_move_constructible_v<Table::IndexType_id0id1id2id3id4id5id6id7>);
    static_assert(!std::is_move_assignable_v<Table::IndexType_id0id1id2id3id4id5id6id7>);

    constexpr auto& table = sqt::Table<Entity8Index>;

    auto indexes = table.GetAbstractIndexes();
    ASSERT_EQ(indexes.size(), 1);
    ASSERT_EQ(indexes[0], &table.Index_id0id1id2id3id4id5id6id7);

    auto index_name = table.Index_id0id1id2id3id4id5id6id7.GetName();
    ASSERT_EQ(index_name, "Entity8Index_Index_id0id1id2id3id4id5id6id7");

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

    constexpr bool is_unique = table.Index_id0id1id2id3id4id5id6id7.IsUnique();
    ASSERT_FALSE(is_unique);
}


TEST(ORMSupportTest, UniqueIndex) {

    using Table = sqt::TableType<EntityUniqueIndex>;
    static_assert(!std::is_copy_constructible_v<Table::IndexType_id0>);
    static_assert(!std::is_copy_assignable_v<Table::IndexType_id0>);
    static_assert(!std::is_move_constructible_v<Table::IndexType_id0>);
    static_assert(!std::is_move_assignable_v<Table::IndexType_id0>);

    constexpr auto& table = sqt::Table<EntityUniqueIndex>;

    auto indexes = table.GetAbstractIndexes();
    ASSERT_EQ(indexes.size(), 1);
    ASSERT_EQ(indexes[0], &table.Index_id0);

    auto index_name = table.Index_id0.GetName();
    ASSERT_EQ(index_name, "EntityUniqueIndex_Index_id0");

    auto columns = table.Index_id0.GetAbstractColumns();
    ASSERT_EQ(columns.size(), 1);
    ASSERT_EQ(columns[0], &table.id0);

    constexpr bool is_unique = table.Index_id0.IsUnique();
    ASSERT_TRUE(is_unique);
}