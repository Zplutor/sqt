#include <gtest/gtest.h>
#include <sqt/foundation/sql_error.h>
#include <sqt/orm/data_context.h>
#include <sqt/orm/table_definition.h>
#include "db_test_fixture.h"
#include "unit_test/fixture/test_entities.h"

class InserterTest : public DBTestFixture {
};


TEST_F(InserterTest, InsertEntireEntity) {

    using Context = sqt::DataContext<test_entities::EntityAutoInc>;
    constexpr auto inserter = Context::MakeInserter();

    Context context{ DB() };
    auto executor = context.Prepare(inserter);

    test_entities::EntityAutoInc entity{ 89, "yyx" };
    executor.BeginBind().Bind(entity);
    executor.Execute();
    executor.Reset();

    {
        auto statement = DB()->PrepareStatement(std::format("select * from EntityAutoInc"));
        ASSERT_TRUE(statement.Step().HasMore());
        ASSERT_EQ(statement.GetColumnInt(0), 89);
        ASSERT_EQ(statement.GetColumnText(1), "yyx");
    }

    //Inserting the same entity again will cause a conflict
    ASSERT_THROW(executor.Execute(), sqt::SQLError);
}


TEST_F(InserterTest, ReplaceEntireEntity) {

    using Context = sqt::DataContext<test_entities::EntityAutoInc>;
    constexpr auto inserter = Context::MakeReplacer();

    Context context{ DB() };
    auto executor = context.Prepare(inserter);
    test_entities::EntityAutoInc entity{ 890, "replacer" };
    executor.BeginBind().Bind(entity);
    executor.Execute();
    executor.Reset();

    //This will replace the previous entity
    executor.Execute();

    auto statement = DB()->PrepareStatement(std::format("select * from EntityAutoInc"));
    ASSERT_TRUE(statement.Step().HasMore());
    ASSERT_EQ(statement.GetColumnInt(0), 890);
    ASSERT_EQ(statement.GetColumnText(1), "replacer");
}


TEST_F(InserterTest, InsertAutoIncEntity) {

    using Context = sqt::DataContext<test_entities::EntityAutoInc>;
    constexpr auto inserter = Context::MakeAutoIncInserter();

    Context context{ DB() };
    auto executor = context.Prepare(inserter);

    for (int index = 1; index <= 3; ++index) {
        test_entities::EntityAutoInc entity{ 1, std::to_string(index) };
        executor.BeginBind().Bind(entity);
        executor.Execute();
        executor.Reset();
    }
    test_entities::EntityAutoInc entity{ 1, "1" };
    executor.BeginBind().Bind(entity);
    //This will cause a conflict
    ASSERT_THROW(executor.Execute(), sqt::SQLError);

    auto statement = DB()->PrepareStatement(std::format("select * from EntityAutoInc"));
    for (int index = 1; index <= 3; ++index) {
        ASSERT_TRUE(statement.Step().HasMore());
        ASSERT_EQ(statement.GetColumnInt(0), index);
        ASSERT_EQ(statement.GetColumnText(1), std::to_string(index));
    }
    ASSERT_FALSE(statement.Step().HasMore());
}


namespace inserter_test {
struct ColumnInserterEntity {
    std::optional<int> id;
    std::optional<std::string> name;
};
SQT_TABLE_BEGIN(ColumnInserterEntity, ColumnInserterEntity)
SQT_COLUMN_FIELD(id, id)
SQT_COLUMN_FIELD(name, name)
SQT_TABLE_END
}
SQT_REGISTER(inserter_test::ColumnInserterEntity)

TEST_F(InserterTest, InsertColumns) {

    using Context = sqt::DataContext<inserter_test::ColumnInserterEntity>;
    Context context{ DB() };

    constexpr auto& table = sqt::Table<inserter_test::ColumnInserterEntity>;

    //One column
    {
        constexpr auto inserter = Context::MakeInserter(table.id);
        auto executor = context.Prepare(inserter);
        executor.BeginBind().Bind(inserter_test::ColumnInserterEntity{ 1, "1" });
        executor.Execute();
    }

    //Two columns
    {
        constexpr auto inserter = Context::MakeInserter(table.id, table.name);
        auto executor = context.Prepare(inserter);
        executor.BeginBind().Bind(inserter_test::ColumnInserterEntity{ 2, "2" });
        executor.Execute();
    }

    //One column with conflict action
    {
        constexpr auto inserter = Context::MakeInserter<sqt::ConflictAction::Ignore>(table.id);
        auto executor = context.Prepare(inserter);
        executor.BeginBind().Bind(inserter_test::ColumnInserterEntity{ 3, "3" });
        executor.Execute();
    }

    //Two columns with conflict action
    {
        constexpr auto inserter = 
            Context::MakeInserter<sqt::ConflictAction::Ignore>(table.id, table.name);
        auto executor = context.Prepare(inserter);
        executor.BeginBind().Bind(inserter_test::ColumnInserterEntity{ 4, "4" });
        executor.Execute();
    }

    auto statement = DB()->PrepareStatement(std::format("select * from ColumnInserterEntity"));

    //Insert one column result
    ASSERT_TRUE(statement.Step().HasMore());
    ASSERT_EQ(statement.GetColumnInt(0), 1);
    ASSERT_EQ(statement.GetColumnType(1), sqt::DataType::Null);

    //Insert two columns result
    ASSERT_TRUE(statement.Step().HasMore());
    ASSERT_EQ(statement.GetColumnInt(0), 2);
    ASSERT_EQ(statement.GetColumnText(1), "2");

    //Insert one column with conflict action result
    ASSERT_TRUE(statement.Step().HasMore());
    ASSERT_EQ(statement.GetColumnInt(0), 3);
    ASSERT_EQ(statement.GetColumnType(1), sqt::DataType::Null);

    //Insert two columns with conflict action result
    ASSERT_TRUE(statement.Step().HasMore());
    ASSERT_EQ(statement.GetColumnInt(0), 4);
    ASSERT_EQ(statement.GetColumnText(1), "4");

    ASSERT_FALSE(statement.Step().HasMore());
}


namespace inserter_test {
struct ColumnReplacerEntity {
    int id{};
    std::optional<std::string> name;
};
SQT_TABLE_BEGIN(ColumnReplacerEntity, ColumnReplacerEntity)
SQT_COLUMN_FIELD(id, id)
SQT_COLUMN_FIELD(name, name)
SQT_PRIMARY_KEY(id)
SQT_TABLE_END
}
SQT_REGISTER(inserter_test::ColumnReplacerEntity)

TEST_F(InserterTest, ReplaceColumns) {

    using Context = sqt::DataContext<inserter_test::ColumnReplacerEntity>;
    Context context{ DB() };

    constexpr auto& table = sqt::Table<inserter_test::ColumnReplacerEntity>;

    //One column
    {
        constexpr auto replacer = Context::MakeReplacer(table.id);
        auto executor = context.Prepare(replacer);
        executor.BeginBind().Bind(inserter_test::ColumnReplacerEntity{ 1, "1" });
        executor.Execute();
    }

    //Two columns
    {
        constexpr auto replacer = Context::MakeReplacer(table.id, table.name);
        auto executor = context.Prepare(replacer);
        executor.BeginBind().Bind(inserter_test::ColumnReplacerEntity{ 1, "2" });
        executor.Execute();
    }

    auto statement = DB()->PrepareStatement(std::format("select * from ColumnReplacerEntity"));
    ASSERT_TRUE(statement.Step().HasMore());
    ASSERT_EQ(statement.GetColumnInt(0), 1);
    ASSERT_EQ(statement.GetColumnText(1), "2");
    ASSERT_FALSE(statement.Step().HasMore());
}