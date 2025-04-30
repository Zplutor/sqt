#include <concepts>
#include <gtest/gtest.h>
#include <sqt/orm/table_definition.h>
#include <sqt/orm/table_mapping.h>

namespace index_def_test {
struct IndexEntity {
    int id0{};
    int id1{};
    int id2{};
    int id3{};
    int id4{};
    int id5{};
    int id6{};
    int id7{};
    int id8{};
};
SQT_TABLE_BEGIN(IndexEntity, IndexEntity)
SQT_COLUMN_FIELD(id0, id0)
SQT_COLUMN_FIELD(id1, id1)
SQT_COLUMN_FIELD(id2, id2)
SQT_COLUMN_FIELD(id3, id3)
SQT_COLUMN_FIELD(id4, id4)
SQT_COLUMN_FIELD(id5, id5)
SQT_COLUMN_FIELD(id6, id6)
SQT_COLUMN_FIELD(id7, id7)
SQT_COLUMN_FIELD(id8, id8)

// One column index
SQT_INDEX(id0)
// Two columns index
SQT_INDEX(id0, id1)
// Max columns index
SQT_INDEX(id0, id1, id2, id3, id4, id5, id6, id7)

// One column unique index
SQT_INDEX_UNIQUE(id1)
// Two columns unique index
SQT_INDEX_UNIQUE(id2, id3)

// One column named index
SQT_INDEX_NAMED(OneColumnNamed, id0)
// Two columns named index
SQT_INDEX_NAMED(TwoColumnsNamed, id0, id1);

// One column named unique index
SQT_INDEX_NAMED_UNIQUE(OneColumnNamedUnique, id1)
// Two columns named unique index
SQT_INDEX_NAMED_UNIQUE(TwoColumnsNamedUnique, id2, id3)

SQT_TABLE_END
}

SQT_REGISTER(index_def_test::IndexEntity)


TEST(IndexDefinitionTest, NonCopyableNonMovable) {

    using TableType = sqt::TableType<index_def_test::IndexEntity>;

    {
        // One column index
        static_assert(!std::copyable<TableType::IndexType_id0>);
        static_assert(!std::movable<TableType::IndexType_id0>);

        // Two columns index
        static_assert(!std::copyable<TableType::IndexType_id0id1>);
        static_assert(!std::movable<TableType::IndexType_id0id1>);

        // Max columns index
        static_assert(!std::copyable<TableType::IndexType_id0id1id2id3id4id5id6id7>);
        static_assert(!std::movable<TableType::IndexType_id0id1id2id3id4id5id6id7>);
    }

    {
        // One column unique index
        static_assert(!std::copyable<TableType::IndexType_id1>);
        static_assert(!std::movable<TableType::IndexType_id1>);

        // Two columns unique index
        static_assert(!std::copyable<TableType::IndexType_id2id3>);
        static_assert(!std::movable<TableType::IndexType_id2id3>);
    }

    {
        // One column named index
        static_assert(!std::copyable<TableType::IndexType_OneColumnNamed>);
        static_assert(!std::movable<TableType::IndexType_OneColumnNamed>);

        // Two columns named index
        static_assert(!std::copyable<TableType::IndexType_TwoColumnsNamed>);
        static_assert(!std::movable<TableType::IndexType_TwoColumnsNamed>);
    }

    {
        // One column named unique index
        static_assert(!std::copyable<TableType::IndexType_OneColumnNamedUnique>);
        static_assert(!std::movable<TableType::IndexType_OneColumnNamedUnique>);

        // Two columns named unique index
        static_assert(!std::copyable<TableType::IndexType_TwoColumnsNamedUnique>);
        static_assert(!std::movable<TableType::IndexType_TwoColumnsNamedUnique>);
    }
}


TEST(IndexDefinitionTest, GetName) {

    constexpr auto& table = sqt::Table<index_def_test::IndexEntity>;

    // One column index
    {
        auto index_name = table.Index_id0.GetName();
        ASSERT_EQ(index_name, "IndexEntity_Index_id0");
    }

    // Two columns index
    {
        auto index_name = table.Index_id0id1.GetName();
        ASSERT_EQ(index_name, "IndexEntity_Index_id0id1");
    }

    // Max columns index
    {
        auto index_name = table.Index_id0id1id2id3id4id5id6id7.GetName();
        ASSERT_EQ(index_name, "IndexEntity_Index_id0id1id2id3id4id5id6id7");
    }

    // One column unique index
    {
        auto index_name = table.Index_id1.GetName();
        ASSERT_EQ(index_name, "IndexEntity_Index_id1");
    }

    // Two columns unique index
    {
        auto index_name = table.Index_id2id3.GetName();
        ASSERT_EQ(index_name, "IndexEntity_Index_id2id3");
    }

    // Named index
    {
        auto index_name = table.Index_OneColumnNamed.GetName();
        ASSERT_EQ(index_name, "OneColumnNamed");

        index_name = table.Index_TwoColumnsNamed.GetName();
        ASSERT_EQ(index_name, "TwoColumnsNamed");
    }

    // Named unique index
    {
        auto index_name = table.Index_OneColumnNamedUnique.GetName();
        ASSERT_EQ(index_name, "OneColumnNamedUnique");

        index_name = table.Index_TwoColumnsNamedUnique.GetName();
        ASSERT_EQ(index_name, "TwoColumnsNamedUnique");
    }
}


TEST(IndexDefinitionTest, IsUnique) {

    constexpr auto& table = sqt::Table<index_def_test::IndexEntity>;

    // One column index
    {
        constexpr bool is_unique = table.Index_id0.IsUnique();
        ASSERT_FALSE(is_unique);
    }

    // Two columns index
    {
        constexpr bool is_unique = table.Index_id0id1.IsUnique();
        ASSERT_FALSE(is_unique);
    }

    // Max columns index
    {
        constexpr bool is_unique = table.Index_id0id1id2id3id4id5id6id7.IsUnique();
        ASSERT_FALSE(is_unique);
    }

    // One column unique index
    {
        constexpr bool is_unique = table.Index_id1.IsUnique();
        ASSERT_TRUE(is_unique);
    }

    // Two columns unique index
    {
        constexpr bool is_unique = table.Index_id2id3.IsUnique();
        ASSERT_TRUE(is_unique);
    }

    // Named index
    {
        {
            constexpr bool is_unique = table.Index_OneColumnNamed.IsUnique();
            ASSERT_FALSE(is_unique);
        }
        {
            constexpr bool is_unique = table.Index_TwoColumnsNamed.IsUnique();
            ASSERT_FALSE(is_unique);
        }
    }

    // Named unique index
    {
        {
            constexpr bool is_unique = table.Index_OneColumnNamedUnique.IsUnique();
            ASSERT_TRUE(is_unique);
        }
        {
            constexpr bool is_unique = table.Index_TwoColumnsNamedUnique.IsUnique();
            ASSERT_TRUE(is_unique);
        }
    }
}


TEST(IndexDefinitionTest, GetAbstractColumns) {

    constexpr auto& table = sqt::Table<index_def_test::IndexEntity>;

    // One column index
    {
        auto columns = table.Index_id0.GetAbstractColumns();
        ASSERT_EQ(columns.size(), 1);
        ASSERT_EQ(columns[0], &table.id0);
    }

    // Two columns index
    {
        auto columns = table.Index_id0id1.GetAbstractColumns();
        ASSERT_EQ(columns.size(), 2);
        ASSERT_EQ(columns[0], &table.id0);
        ASSERT_EQ(columns[1], &table.id1);
    }

    // Max columns index
    {
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

    // One column unique index
    {
        auto columns = table.Index_id1.GetAbstractColumns();
        ASSERT_EQ(columns.size(), 1);
        ASSERT_EQ(columns[0], &table.id1);
    }

    // Two columns unique index
    {
        auto columns = table.Index_id2id3.GetAbstractColumns();
        ASSERT_EQ(columns.size(), 2);
        ASSERT_EQ(columns[0], &table.id2);
        ASSERT_EQ(columns[1], &table.id3);
    }

    // One column named index
    {
        auto columns = table.Index_OneColumnNamed.GetAbstractColumns();
        ASSERT_EQ(columns.size(), 1);
        ASSERT_EQ(columns[0], &table.id0);
    }

    // Two columns named index
    {
        auto columns = table.Index_TwoColumnsNamed.GetAbstractColumns();
        ASSERT_EQ(columns.size(), 2);
        ASSERT_EQ(columns[0], &table.id0);
        ASSERT_EQ(columns[1], &table.id1);
    }

    // One column named unique index
    {
        auto columns = table.Index_OneColumnNamedUnique.GetAbstractColumns();
        ASSERT_EQ(columns.size(), 1);
        ASSERT_EQ(columns[0], &table.id1);
    }

    // Two columns named unique index
    {
        auto columns = table.Index_TwoColumnsNamedUnique.GetAbstractColumns();
        ASSERT_EQ(columns.size(), 2);
        ASSERT_EQ(columns[0], &table.id2);
        ASSERT_EQ(columns[1], &table.id3);
    }
}