#pragma once

#include <sqt/orm/table_definition.h>

namespace test_entities {

/**
Entity without primary key.
*/
struct EntityNoPK {
    int id{};
    std::string name;
    friend auto operator<=>(const EntityNoPK&, const EntityNoPK&) = default;
};
SQT_TABLE_BEGIN(EntityNoPK, EntityNoPK)
SQT_COLUMN_FIELD(ID, id)
SQT_COLUMN_FIELD(Name, name)
SQT_TABLE_END


/**
Entity with single column primary key.
*/
struct EntityPK1 {
    int id{};
    std::string name;
    friend auto operator<=>(const EntityPK1&, const EntityPK1&) = default;
};
SQT_TABLE_BEGIN(EntityPK1, EntityPK1)
SQT_COLUMN_FIELD(ID, id)
SQT_COLUMN_FIELD(Name, name)
SQT_PRIMARY_KEY(ID)
SQT_TABLE_END


/**
Entity with multiple column primary key.
*/
struct EntityPK2 {
    int id{};
    std::string name;
    int age{};
    friend auto operator<=>(const EntityPK2&, const EntityPK2&) = default;
};
SQT_TABLE_BEGIN(EntityPK2, EntityPK2)
SQT_COLUMN_FIELD(ID, id)
SQT_COLUMN_FIELD(Name, name)
SQT_COLUMN_FIELD(Age, age)
SQT_PRIMARY_KEY(ID, Name)
SQT_TABLE_END


/**
Entity with autoincrement primary key.
*/
struct EntityAutoInc {
    int id{};
    std::string name;
    friend auto operator<=>(const EntityAutoInc&, const EntityAutoInc&) = default;
};
SQT_TABLE_BEGIN(EntityAutoInc, EntityAutoInc)
SQT_COLUMN_FIELD(id, id)
SQT_COLUMN_FIELD(name, name)
SQT_PRIMARY_KEY_AUTO_INC(id)
SQT_INDEX_UNIQUE(name)
SQT_TABLE_END

}

SQT_REGISTER(test_entities::EntityNoPK)
SQT_REGISTER(test_entities::EntityPK1)
SQT_REGISTER(test_entities::EntityPK2)
SQT_REGISTER(test_entities::EntityAutoInc)
