#include <gtest/gtest.h>
#include <sqt/foundation/sql_error.h>
#include <sqt/orm/data_context.h>
#include <sqt/orm/orm_support.h>
#include "db_test_fixture.h"

class InserterTest : public DBTestFixture {
};


namespace inserter_test {
class Entity {
public:
    int id{};
    std::string name;
};
SQT_TABLE_BEGIN(Entity, Entity)
SQT_COLUMN(id, id)
SQT_COLUMN(name, name)
SQT_PRIMARY_KEY_AUTO_INC(id)
SQT_TABLE_END
}
SQT_REGISTER(inserter_test, Entity)

TEST_F(InserterTest, InsertEntireEntity) {

    using Context = sqt::DataContext<inserter_test::Entity>;
    constexpr auto inserter = Context::MakeInserter();

    Context context{ DB() };
    auto executor = context.Prepare(inserter);

    inserter_test::Entity entity{ 89, "yyx" };
    executor.BeginBind().Bind(entity);
    executor.Execute();
    executor.Reset();

    {
        auto statement = DB()->PrepareStatement(std::format("select * from Entity"));
        ASSERT_TRUE(statement.Step());
        ASSERT_EQ(statement.GetColumnInt(0), 89);
        ASSERT_EQ(statement.GetColumnText(1), "yyx");
    }

    //Inserting the same entity again will cause a conflict
    ASSERT_THROW(executor.Execute(), sqt::SQLError);
}


TEST_F(InserterTest, ReplaceEntireEntity) {

    using Context = sqt::DataContext<inserter_test::Entity>;
    constexpr auto inserter = Context::MakeReplacer();

    Context context{ DB() };
    auto executor = context.Prepare(inserter);
    inserter_test::Entity entity{ 890, "replacer" };
    executor.BeginBind().Bind(entity);
    executor.Execute();
    executor.Reset();

    //This will replace the previous entity
    executor.Execute();

    auto statement = DB()->PrepareStatement(std::format("select * from Entity"));
    ASSERT_TRUE(statement.Step());
    ASSERT_EQ(statement.GetColumnInt(0), 890);
    ASSERT_EQ(statement.GetColumnText(1), "replacer");
}


namespace inserter_test {
class EntityWithUniqueIndex {
public:
    int id{};
    std::string name;
};
SQT_TABLE_BEGIN(EntityWithUniqueIndex, EntityWithUniqueIndex)
SQT_COLUMN(id, id)
SQT_COLUMN(name, name)
SQT_PRIMARY_KEY_AUTO_INC(id)
SQT_INDEX_UNIQUE(name)
SQT_TABLE_END
}
SQT_REGISTER(inserter_test, EntityWithUniqueIndex)

TEST_F(InserterTest, InsertAutoIncEntity) {

    using Context = sqt::DataContext<inserter_test::EntityWithUniqueIndex>;
    constexpr auto inserter = Context::MakeAutoIncInserter();

    Context context{ DB() };
    auto executor = context.Prepare(inserter);

    for (int index = 1; index <= 3; ++index) {
        inserter_test::EntityWithUniqueIndex entity{ 1, std::to_string(index) };
        executor.BeginBind().Bind(entity);
        executor.Execute();
        executor.Reset();
    }
    inserter_test::EntityWithUniqueIndex entity{ 1, "1" };
    executor.BeginBind().Bind(entity);
    //This will cause a conflict
    ASSERT_THROW(executor.Execute(), sqt::SQLError);

    auto statement = DB()->PrepareStatement(std::format("select * from EntityWithUniqueIndex"));
    for (int index = 1; index <= 3; ++index) {
        ASSERT_TRUE(statement.Step());
        ASSERT_EQ(statement.GetColumnInt(0), index);
        ASSERT_EQ(statement.GetColumnText(1), std::to_string(index));
    }
    ASSERT_FALSE(statement.Step());
}


TEST_F(InserterTest, ReplaceAutoIncEntity) {

    using Context = sqt::DataContext<inserter_test::EntityWithUniqueIndex>;
    constexpr auto replacer = Context::MakeAutoIncReplacer();

    Context context{ DB() };
    auto executor = context.Prepare(replacer);

    for (int index = 1; index <= 3; ++index) {
        inserter_test::EntityWithUniqueIndex entity{ 1, "replace"};
        executor.BeginBind().Bind(entity);
        executor.Execute();
        executor.Reset();
    }

    auto statement = DB()->PrepareStatement(std::format("select * from EntityWithUniqueIndex"));
    ASSERT_TRUE(statement.Step());
    ASSERT_EQ(statement.GetColumnInt(0), 3);
    ASSERT_EQ(statement.GetColumnText(1), "replace");

    ASSERT_FALSE(statement.Step());
}