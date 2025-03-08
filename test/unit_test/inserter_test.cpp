#include <gtest/gtest.h>
#include <sqt/foundation/sql_error.h>
#include <sqt/orm/data_context.h>
#include <sqt/orm/orm_support.h>
#include "db_test_fixture.h"
#include "unit_test/test_entities.h"

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
        ASSERT_TRUE(statement.Step());
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
    ASSERT_TRUE(statement.Step());
    ASSERT_EQ(statement.GetColumnInt(0), 890);
    ASSERT_EQ(statement.GetColumnText(1), "replacer");
}


TEST_F(InserterTest, DataContextReplace) {

    sqt::DataContext<test_entities::EntityAutoInc> context{ DB() };
    test_entities::EntityAutoInc entity{ 890, "replacer" };
    context.Replace(entity);
    //This will replace the previous entity
    context.Replace(entity);

    auto statement = DB()->PrepareStatement(std::format("select * from EntityAutoInc"));
    ASSERT_TRUE(statement.Step());
    ASSERT_EQ(statement.GetColumnInt(0), 890);
    ASSERT_EQ(statement.GetColumnText(1), "replacer");
    ASSERT_FALSE(statement.Step());
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
        ASSERT_TRUE(statement.Step());
        ASSERT_EQ(statement.GetColumnInt(0), index);
        ASSERT_EQ(statement.GetColumnText(1), std::to_string(index));
    }
    ASSERT_FALSE(statement.Step());
}