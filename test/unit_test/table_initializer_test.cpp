#include <gtest/gtest.h>
#include <filesystem>
#include <sqt/foundation/database.h>
#include <sqt/orm/orm_support.h>
#include <sqt/orm/table/table_initializer.h>
#include "db_test_fixture.h"

class TableInitializerTest : public DBTestFixture {

};

namespace table_initializer_test {
struct EntityNoPK {
    int integer_field{};
    std::optional<int> nullable_integer_field;
    std::string string_field;
    std::optional<std::string> nullable_string_field;
};
SQT_TABLE_BEGIN(EntityNoPK, EntityNoPK)
SQT_COLUMN_FIELD(IntegerField, integer_field)
SQT_COLUMN_FIELD(StringField, string_field)
SQT_COLUMN_FIELD(NullableIntegerField, nullable_integer_field)
SQT_COLUMN_FIELD(NullableStringField, nullable_string_field)
SQT_TABLE_END
}
SQT_REGISTER(table_initializer_test::EntityNoPK)

TEST_F(TableInitializerTest, NewTableNoPK) {

    sqt::TableInitializer::Initialize(
        sqt::TableV<table_initializer_test::EntityNoPK>, 
        *DB());

    auto table_info = DB()->GetTableInfo("EntityNoPK");
    ASSERT_TRUE(table_info.has_value());
    ASSERT_EQ(table_info->columns.size(), 4);

    {
        const auto& column0 = table_info->columns[0];
        ASSERT_EQ(column0.name, "IntegerField");
        ASSERT_EQ(column0.data_type, sqt::DataType::Integer);
        ASSERT_EQ(column0.is_nullable, false);
        ASSERT_EQ(column0.is_primary_key, false);
    }

    {
        const auto& column1 = table_info->columns[1];
        ASSERT_EQ(column1.name, "StringField");
        ASSERT_EQ(column1.data_type, sqt::DataType::Text);
        ASSERT_EQ(column1.is_nullable, false);
        ASSERT_EQ(column1.is_primary_key, false);
    }

    {
        const auto& column2 = table_info->columns[2];
        ASSERT_EQ(column2.name, "NullableIntegerField");
        ASSERT_EQ(column2.data_type, sqt::DataType::Integer);
        ASSERT_EQ(column2.is_nullable, true);
        ASSERT_EQ(column2.is_primary_key, false);
    }

    {
        const auto& column3 = table_info->columns[3];
        ASSERT_EQ(column3.name, "NullableStringField");
        ASSERT_EQ(column3.data_type, sqt::DataType::Text);
        ASSERT_EQ(column3.is_nullable, true);
        ASSERT_EQ(column3.is_primary_key, false);
    }
}


namespace table_initializer_test {
struct EntityPK1 {
    int integer_field{};
    std::string string_field;
};
SQT_TABLE_BEGIN(EntityPK1, EntityPK1)
SQT_COLUMN_FIELD(IntegerField, integer_field)
SQT_COLUMN_FIELD(StringField, string_field)
SQT_PRIMARY_KEY(IntegerField)
SQT_TABLE_END
}
SQT_REGISTER(table_initializer_test::EntityPK1)

TEST_F(TableInitializerTest, NewTablePK1) {

    sqt::TableInitializer::Initialize(
        sqt::TableV<table_initializer_test::EntityPK1>,
        *DB());

    auto table_info = DB()->GetTableInfo("EntityPK1");
    ASSERT_TRUE(table_info.has_value());
    ASSERT_EQ(table_info->columns.size(), 2);

    {
        const auto& column0 = table_info->columns[0];
        ASSERT_EQ(column0.name, "IntegerField");
        ASSERT_EQ(column0.data_type, sqt::DataType::Integer);
        ASSERT_EQ(column0.is_nullable, false);
        ASSERT_EQ(column0.is_primary_key, true);
    }
}


namespace table_initializer_test {
struct EntityPK1AutoInc {
    int integer_field{};
    std::string string_field;
};
SQT_TABLE_BEGIN(EntityPK1AutoInc, EntityPK1AutoInc)
SQT_COLUMN_FIELD(IntegerField, integer_field)
SQT_COLUMN_FIELD(StringField, string_field)
SQT_PRIMARY_KEY_AUTO_INC(IntegerField)
SQT_TABLE_END;
}
SQT_REGISTER(table_initializer_test::EntityPK1AutoInc)

TEST_F(TableInitializerTest, NewTablePK1AutoInc) {

    sqt::TableInitializer::Initialize(
        sqt::TableV<table_initializer_test::EntityPK1AutoInc>,
        *DB());

    auto table_info = DB()->GetTableInfo("EntityPK1AutoInc");
    ASSERT_TRUE(table_info.has_value());
    ASSERT_EQ(table_info->columns.size(), 2);

    {
        const auto& column0 = table_info->columns[0];
        ASSERT_EQ(column0.name, "IntegerField");
        ASSERT_EQ(column0.data_type, sqt::DataType::Integer);
        ASSERT_EQ(column0.is_nullable, false);
        ASSERT_EQ(column0.is_primary_key, true);
    }

    DB()->ExecuteSQL("insert into EntityPK1AutoInc (StringField) values ('1')");
    ASSERT_EQ(DB()->LastInsertRowID(), 1);
    DB()->ExecuteSQL("insert into EntityPK1AutoInc (StringField) values ('2')");
    ASSERT_EQ(DB()->LastInsertRowID(), 2);
}


namespace table_initializer_test {
struct EntityPK2 {
    int integer_field{};
    std::string string_field;
};
SQT_TABLE_BEGIN(EntityPK2, EntityPK2)
SQT_COLUMN_FIELD(IntegerField, integer_field)
SQT_COLUMN_FIELD(StringField, string_field)
SQT_PRIMARY_KEY(IntegerField, StringField)
SQT_TABLE_END
}
SQT_REGISTER(table_initializer_test::EntityPK2)

TEST_F(TableInitializerTest, NewTablePK2) {

    sqt::TableInitializer::Initialize(
        sqt::TableV<table_initializer_test::EntityPK2>, 
        *DB());

    auto table_info = DB()->GetTableInfo("EntityPK2");
    ASSERT_TRUE(table_info.has_value());
    ASSERT_EQ(table_info->columns.size(), 2);

    {
        const auto& column0 = table_info->columns[0];
        ASSERT_EQ(column0.name, "IntegerField");
        ASSERT_EQ(column0.data_type, sqt::DataType::Integer);
        ASSERT_EQ(column0.is_nullable, false);
        ASSERT_EQ(column0.is_primary_key, true);
    }

    {
        const auto& column1 = table_info->columns[1];
        ASSERT_EQ(column1.name, "StringField");
        ASSERT_EQ(column1.data_type, sqt::DataType::Text);
        ASSERT_EQ(column1.is_nullable, false);
        ASSERT_EQ(column1.is_primary_key, true);
    }
}


namespace table_initializer_test {
namespace old_table {
struct OldTable {
    int integer_field{};
};
SQT_TABLE_BEGIN(AlterTable, OldTable)
SQT_COLUMN_FIELD(IntField, integer_field)
SQT_TABLE_END
}
namespace new_table {
struct NewTable {
    int integer_field{};
    std::string string_field;
};
SQT_TABLE_BEGIN(AlterTable, NewTable)
SQT_COLUMN_FIELD(IntField, integer_field)
SQT_COLUMN_FIELD(StringField, string_field)
SQT_TABLE_END
}
}
SQT_REGISTER(table_initializer_test::old_table::AlterTable)
SQT_REGISTER(table_initializer_test::new_table::AlterTable)

TEST_F(TableInitializerTest, AlterTable) {

    sqt::TableInitializer::Initialize(
        sqt::TableV<table_initializer_test::old_table::OldTable>, 
        *DB());
    auto old_table_info = DB()->GetTableInfo("AlterTable");
    ASSERT_TRUE(old_table_info.has_value());
    ASSERT_EQ(old_table_info->columns.size(), 1);

    sqt::TableInitializer::Initialize(
        sqt::TableV<table_initializer_test::new_table::NewTable>, 
        *DB());
    auto new_table_info = DB()->GetTableInfo("AlterTable");
    ASSERT_TRUE(new_table_info.has_value());
    ASSERT_EQ(new_table_info->columns.size(), 2);

    {
        const auto& column0 = new_table_info->columns[0];
        ASSERT_EQ(column0.name, "IntField");
        ASSERT_EQ(column0.data_type, sqt::DataType::Integer);
        ASSERT_EQ(column0.is_nullable, false);
        ASSERT_EQ(column0.is_primary_key, false);
    }

    {
        const auto& column1 = new_table_info->columns[1];
        ASSERT_EQ(column1.name, "StringField");
        ASSERT_EQ(column1.data_type, sqt::DataType::Text);
        ASSERT_EQ(column1.is_nullable, false);
        ASSERT_EQ(column1.is_primary_key, false);
    }

    // Initialize new table again to make sure there is no error.
    ASSERT_NO_THROW(
        sqt::TableInitializer::Initialize(
            sqt::TableV<table_initializer_test::new_table::NewTable>,
            *DB()));
}


namespace table_initializer_test {
struct EntityWithIndex {
    int id{};
    std::string name;
    int age{};
};
SQT_TABLE_BEGIN(EntityWithIndex, EntityWithIndex)
SQT_COLUMN_FIELD(id, id)
SQT_COLUMN_FIELD(name, name)
SQT_COLUMN_FIELD(age, age)
SQT_INDEX(id)
SQT_INDEX(id, name)
SQT_INDEX(id, name, age)
SQT_INDEX_UNIQUE(id, age)
SQT_TABLE_END
}
SQT_REGISTER(table_initializer_test::EntityWithIndex)

TEST_F(TableInitializerTest, CreateIndex) {

    auto& table = sqt::TableV<table_initializer_test::EntityWithIndex>;

    sqt::TableInitializer::Initialize(table, *DB());

    auto index_info = DB()->GetIndexInfo("EntityWithIndex_Index_id");
    ASSERT_TRUE(index_info.has_value());
    ASSERT_EQ(index_info->columns.size(), 1);
    ASSERT_EQ(index_info->columns[0], "id");

    index_info = DB()->GetIndexInfo("EntityWithIndex_Index_idname");
    ASSERT_TRUE(index_info.has_value());
    ASSERT_EQ(index_info->columns.size(), 2);
    ASSERT_EQ(index_info->columns[0], "id");
    ASSERT_EQ(index_info->columns[1], "name");

    index_info = DB()->GetIndexInfo("EntityWithIndex_Index_idnameage");
    ASSERT_TRUE(index_info.has_value());
    ASSERT_EQ(index_info->columns.size(), 3);
    ASSERT_EQ(index_info->columns[0], "id");
    ASSERT_EQ(index_info->columns[1], "name");
    ASSERT_EQ(index_info->columns[2], "age");

    index_info = DB()->GetIndexInfo("EntityWithIndex_index_idage");
    ASSERT_TRUE(index_info.has_value());
    ASSERT_EQ(index_info->columns.size(), 2);
    ASSERT_EQ(index_info->columns[0], "id");
    ASSERT_EQ(index_info->columns[1], "age");
}