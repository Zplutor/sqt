#include <gtest/gtest.h>
#include <sqt/foundation/sql_error.h>
#include <sqt/orm/data_context.h>
#include <sqt/orm/table_definition.h>
#include "unit_test/db_test_fixture.h"
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
    int id{};
    std::optional<std::string> name;
};
SQT_TABLE_BEGIN(ColumnInserterEntity, ColumnInserterEntity)
SQT_COLUMN_FIELD(id, id)
SQT_COLUMN_FIELD(name, name)
SQT_PRIMARY_KEY(id)
SQT_TABLE_END
}
SQT_REGISTER(inserter_test::ColumnInserterEntity)

TEST_F(InserterTest, InsertColumns_NoConflictAction) {

    using Context = sqt::DataContext<inserter_test::ColumnInserterEntity>;
    Context context{ DB() };

    constexpr auto& table = sqt::Table<inserter_test::ColumnInserterEntity>;

    //One columns
    {
        //Inline
        {
            constexpr auto inserter = Context::MakeInserter(table.id = 1);
            auto executor = context.Prepare(inserter);
            executor.Execute();
        }

        //Placeholder
        {
            constexpr auto inserter = Context::MakeInserter(table.id = sqt::_);
            auto executor = context.Prepare(inserter);
            executor.BeginBind().Bind(2);
            executor.Execute();
        }
    }

    //Two columns
    {
        //Inline
        {
            auto inserter = Context::MakeInserter(table.id = 3, table.name = "3");
            auto executor = context.Prepare(inserter);
            executor.Execute();
        }

        //Placeholder
        {
            auto inserter = Context::MakeInserter(table.id = sqt::_, table.name = sqt::_);
            auto executor = context.Prepare(inserter);
            executor.BeginBind().Bind(4).Bind("4");
            executor.Execute();
        }
    }

    auto statement = DB()->PrepareStatement(std::format("select * from ColumnInserterEntity"));

    //One column, inline
    ASSERT_TRUE(statement.Step().HasMore());
    ASSERT_EQ(statement.GetColumnInt(0), 1);
    ASSERT_EQ(statement.GetColumnType(1), sqt::DataType::Null);

    //One column, placeholder
    ASSERT_TRUE(statement.Step().HasMore());
    ASSERT_EQ(statement.GetColumnInt(0), 2);
    ASSERT_EQ(statement.GetColumnType(1), sqt::DataType::Null);

    //Two columns, inline
    ASSERT_TRUE(statement.Step().HasMore());
    ASSERT_EQ(statement.GetColumnInt(0), 3);
    ASSERT_EQ(statement.GetColumnText(1), "3");

    //Two columns, placeholder
    ASSERT_TRUE(statement.Step().HasMore());
    ASSERT_EQ(statement.GetColumnInt(0), 4);
    ASSERT_EQ(statement.GetColumnText(1), "4");

    ASSERT_FALSE(statement.Step().HasMore());
}


TEST_F(InserterTest, InsertColumns_ConflictAction) {

    using Context = sqt::DataContext<inserter_test::ColumnInserterEntity>;
    Context context{ DB() };

    constexpr auto& table = sqt::Table<inserter_test::ColumnInserterEntity>;

    //One columns
    {
        constexpr auto inserter = Context::MakeInserter<sqt::ConflictAction::Ignore>(table.id = 1);
        auto executor = context.Prepare(inserter);
        executor.Execute();
    }

    //Two columns
    {
        //Inline
        auto inserter = 
            Context::MakeInserter<sqt::ConflictAction::Rollback>(table.id = 3, table.name = "3");
        auto executor = context.Prepare(inserter);
        executor.Execute();
    }

    auto statement = DB()->PrepareStatement(std::format("select * from ColumnInserterEntity"));

    //One column
    ASSERT_TRUE(statement.Step().HasMore());
    ASSERT_EQ(statement.GetColumnInt(0), 1);
    ASSERT_EQ(statement.GetColumnType(1), sqt::DataType::Null);
    //Two columns
    ASSERT_TRUE(statement.Step().HasMore());
    ASSERT_EQ(statement.GetColumnInt(0), 3);
    ASSERT_EQ(statement.GetColumnText(1), "3");

    ASSERT_FALSE(statement.Step().HasMore());
}


TEST_F(InserterTest, ReplaceColumns) {

    using Context = sqt::DataContext<inserter_test::ColumnInserterEntity>;
    Context context{ DB() };

    constexpr auto& table = sqt::Table<inserter_test::ColumnInserterEntity>;

    //One column
    {
        //Inline
        {
            constexpr auto replacer = Context::MakeReplacer(table.id = 1);
            auto executor = context.Prepare(replacer);
            executor.Execute();
        }

        //Placeholder
        {
            constexpr auto replacer = Context::MakeReplacer(table.id = sqt::_);
            auto executor = context.Prepare(replacer);
            executor.BeginBind().Bind(2);
            executor.Execute();
        }
    }

    //Two columns
    {
        //Inline
        {
            auto replacer = Context::MakeReplacer(table.id = 1, table.name = "3");
            auto executor = context.Prepare(replacer);
            executor.Execute();
        }

        //Placeholder
        {
            auto replacer = Context::MakeReplacer(table.id = sqt::_, table.name = sqt::_);
            auto executor = context.Prepare(replacer);
            executor.BeginBind().Bind(2).Bind("4");
            executor.Execute();
        }
    }

    auto statement = DB()->PrepareStatement(std::format("select * from ColumnInserterEntity"));

    ASSERT_TRUE(statement.Step().HasMore());
    ASSERT_EQ(statement.GetColumnInt(0), 1);
    ASSERT_EQ(statement.GetColumnText(1), "3");

    ASSERT_TRUE(statement.Step().HasMore());
    ASSERT_EQ(statement.GetColumnInt(0), 2);
    ASSERT_EQ(statement.GetColumnText(1), "4");

    ASSERT_FALSE(statement.Step().HasMore());
}



TEST_F(InserterTest, InsertColumns_PK) {

    //One column PK
    {
        using Context = sqt::DataContext<test_entities::EntityPK1>;
        constexpr auto& table = sqt::Table<test_entities::EntityPK1>;

        auto inserter = Context::MakeInserter(table.PrimaryKey = 11, table.Name = "11");

        Context context{ DB() };
        auto executor = context.Prepare(inserter);
        executor.Execute();

        auto statement = DB()->PrepareStatement(std::format("select * from EntityPK1"));
        ASSERT_TRUE(statement.Step().HasMore());
        ASSERT_EQ(statement.GetColumnInt(0), 11);
        ASSERT_EQ(statement.GetColumnText(1), "11");
    }

    //Two columns PK
    {
        using Context = sqt::DataContext<test_entities::EntityPK2>;
        constexpr auto& table = sqt::Table<test_entities::EntityPK2>;

        auto inserter = Context::MakeInserter(
            table.PrimaryKey = std::make_tuple(10, "ab"),
            table.Age = 100);

        Context context{ DB() };
        auto executor = context.Prepare(inserter);
        executor.Execute();

        auto statement = DB()->PrepareStatement(std::format("select * from EntityPK2"));
        ASSERT_TRUE(statement.Step().HasMore());
        ASSERT_EQ(statement.GetColumnInt(0), 10);
        ASSERT_EQ(statement.GetColumnText(1), "ab");
        ASSERT_EQ(statement.GetColumnInt(2), 100);
    }
}


TEST_F(InserterTest, ReplaceColumns_PK) {

    //One column PK
    {
        using Context = sqt::DataContext<test_entities::EntityPK1>;
        constexpr auto& table = sqt::Table<test_entities::EntityPK1>;

        auto inserter = Context::MakeReplacer(table.PrimaryKey = 12, table.Name = "dd");

        Context context{ DB() };
        auto executor = context.Prepare(inserter);
        executor.Execute();

        auto statement = DB()->PrepareStatement(std::format("select * from EntityPK1"));
        ASSERT_TRUE(statement.Step().HasMore());
        ASSERT_EQ(statement.GetColumnInt(0), 12);
        ASSERT_EQ(statement.GetColumnText(1), "dd");
    }

    //Two columns PK
    {
        using Context = sqt::DataContext<test_entities::EntityPK2>;
        constexpr auto& table = sqt::Table<test_entities::EntityPK2>;

        auto inserter = Context::MakeReplacer(
            table.PrimaryKey = std::make_tuple(20, "CD"),
            table.Age = 20);

        Context context{ DB() };
        auto executor = context.Prepare(inserter);
        executor.Execute();

        auto statement = DB()->PrepareStatement(std::format("select * from EntityPK2"));
        ASSERT_TRUE(statement.Step().HasMore());
        ASSERT_EQ(statement.GetColumnInt(0), 20);
        ASSERT_EQ(statement.GetColumnText(1), "CD");
        ASSERT_EQ(statement.GetColumnInt(2), 20);
    }
}