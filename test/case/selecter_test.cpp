#include <gtest/gtest.h>
#include <sqt/orm/data_context.h>
#include <sqt/orm/orm_support.h>
#include <sqt/foundation/database.h>

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

}