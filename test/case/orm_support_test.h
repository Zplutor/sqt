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


struct EntityPK1 {
    int id0{};
    int id1{};
};
SQT_TABLE_BEGIN(EntityPK1, EntityPK1)
SQT_COLUMN(id0, id0)
SQT_COLUMN(id1, id1)
SQT_PRIMARY_KEY(id0)
SQT_TABLE_END


struct EntityPK2 {
    int id0{};
    int id1{};
    int id2{};
};
SQT_TABLE_BEGIN(EntityPK2, EntityPK2)
SQT_COLUMN(id0, id0)
SQT_COLUMN(id1, id1)
SQT_COLUMN(id2, id2)
SQT_PRIMARY_KEY(id0, id1)
SQT_TABLE_END


struct EntityPKAutoInc {
    int id{};
};
SQT_TABLE_BEGIN(EntityPKAutoInc, EntityPKAutoInc)
SQT_COLUMN(id, id)
SQT_PRIMARY_KEY_AUTOINCREMENT(id)
SQT_TABLE_END


struct Entity1Index {
    int id0{};
    int id1{};
};
SQT_TABLE_BEGIN(Entity1Index, Entity1Index)
SQT_COLUMN(id0, id0)
SQT_COLUMN(id1, id1)
SQT_INDEX(id0)
SQT_TABLE_END


struct Entity2Index {
    int id0{};
    int id1{};
    int id2{};
};
SQT_TABLE_BEGIN(Entity2Index, Entity2Index)
SQT_COLUMN(id0, id0)
SQT_COLUMN(id1, id1)
SQT_COLUMN(id2, id2)
SQT_INDEX(id0, id1)
SQT_TABLE_END


struct Entity8Index {
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
SQT_TABLE_BEGIN(Entity8Index, Entity8Index)
SQT_COLUMN(id0, id0)
SQT_COLUMN(id1, id1)
SQT_COLUMN(id2, id2)
SQT_COLUMN(id3, id3)
SQT_COLUMN(id4, id4)
SQT_COLUMN(id5, id5)
SQT_COLUMN(id6, id6)
SQT_COLUMN(id7, id7)
SQT_INDEX(id0, id1, id2, id3, id4, id5, id6, id7)
SQT_TABLE_END

}


SQT_REGISTER(orm_support, Entity)
SQT_REGISTER(orm_support, Entity0Column)
SQT_REGISTER(orm_support, Entity1Column)
SQT_REGISTER(orm_support, EntityPK1)
SQT_REGISTER(orm_support, EntityPK2)
SQT_REGISTER(orm_support, EntityPKAutoInc)
SQT_REGISTER(orm_support, Entity1Index)
SQT_REGISTER(orm_support, Entity2Index)
SQT_REGISTER(orm_support, Entity8Index)