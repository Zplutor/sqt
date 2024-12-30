#pragma once

#include <string>
#include <sqt/orm/orm_support.h>

struct Entity {
    int int_value{};
    std::string string_value;
};

SQT_TABLE_BEGIN(Entity, Entity)
SQT_COLUMN(IntColumn, int_value)
SQT_COLUMN(StringColumn, string_value)
SQT_TABLE_END


struct Entity0Column {

};

SQT_TABLE_BEGIN(Entity0Column, Entity0Column)
SQT_TABLE_END


struct Entity1Column {
    int id{};
};

SQT_TABLE_BEGIN(Entity1Column, Entity1Column)
SQT_COLUMN(id, id)
SQT_TABLE_END