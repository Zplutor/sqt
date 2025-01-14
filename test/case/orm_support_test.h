#pragma once

#include <optional>
#include <string>
#include <sqt/orm/orm_support.h>

namespace orm_support {

struct Entity {
    int int_value{};
    float float_value{};
    std::string string_value;
    std::optional<int> nullable_int_value;
    std::optional<float> nullable_float_value;
    std::optional<std::string> nullable_string_value;
};

SQT_TABLE_BEGIN(Entity, Entity)
SQT_COLUMN(IntColumn, int_value)
SQT_COLUMN(FloatColumn, float_value)
SQT_COLUMN(StringColumn, string_value)
SQT_COLUMN(NullableIntColumn, nullable_int_value)
SQT_COLUMN(NullableFloatColumn, nullable_float_value)
SQT_COLUMN(NullableStringColumn, nullable_string_value)
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

}


SQT_REGISTER(orm_support, Entity)
SQT_REGISTER(orm_support, Entity0Column)
SQT_REGISTER(orm_support, Entity1Column)