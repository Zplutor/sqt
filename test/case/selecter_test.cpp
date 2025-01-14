#include <gtest/gtest.h>
#include <sqt/orm/data_context.h>
#include <sqt/orm/orm_support.h>
#include <sqt/core/database.h>

struct Entity {
    int id{};
    std::string name;
};

SQT_TABLE_BEGIN(Entity, Entity)
SQT_COLUMN(ID, id)
SQT_COLUMN(Name, name)
SQT_TABLE_END

SQT_REGISTER(, Entity)

TEST(SelecterTest, Test) {

    auto db_path = "Test.db";
    //std::filesystem::remove(db_path);

    auto db = std::make_shared<sqt::Database>(sqt::Database::Open(db_path));

    constexpr auto selecter = sqt::DataContext<Entity>::MakeSelecter();
    constexpr auto limit_selecter = selecter.Limit(1);
    constexpr auto limit_selecter2 = selecter.Limit(sqt::_);

    sqt::DataContext<Entity> data_context{ db };
    
    auto executor = data_context.Prepare(limit_selecter);
    executor.BeginBind();

    auto executor2 = data_context.Prepare(limit_selecter2);
    executor2.BeginBind().Bind(2);
}