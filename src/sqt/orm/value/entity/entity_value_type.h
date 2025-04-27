#pragma once

/**
@file
    Defines concepts for entity value types.
*/

#include <sqt/orm/table_mapping.h>

namespace sqt {

/**
Constrains a type to be an entity value type, which can be mapped to a table type.

@details
    @b Requirements
    - There must be a specialization of `sqt::TableMapping<>` for the type.

    This concept can be used to determine whether a table type is defined for a given entity type
    and is registered to the framework.

    Use the `SQT_TABLE_BEGIN` and `SQT_REGISTER` macros to define a table type and register it.

@see sqt::TableMapping<>
@see SQT_REGISTER
@see SQT_TABLE_BEGIN
*/
template<typename T>
concept EntityValueType = requires {
    typename TableMapping<T>::type;
};


/**
Constrains a type to be an entity value type that has a primary key.

@details
    @b Requirements
    - The type must satisfy the `sqt::EntityValueType` concept.
    - There must be a nested type `PrimaryKeyType` within the corresponding table type.

    Use the `SQT_PRIMARY_KEY` macro to define the primary key for the table.

@see sqt::EntityValueType
@see SQT_PRIMARY_KEY
*/
template<typename T>
concept PrimaryKeyEntityValueType = EntityValueType<T> && requires {
    typename TableType<T>::PrimaryKeyType;
};


/**
Constrains a type to be an entity value type that has an auto-increment primary key.

@details
    @b Requirements
    - The type must satisfy the `sqt::PrimaryKeyEntityValueType` concept.
    - The `IsAutoInc()` method of the primary key of the corresponding table returns `true`.

    Use the `SQT_PRIMARY_KEY_AUTO_INC` macro to define an auto-increment primary key for the table.

@see sqt::PrimaryKeyEntityValueType
@see SQT_PRIMARY_KEY_AUTO_INC
*/
template<typename T>
concept AutoIncEntityValueType = PrimaryKeyEntityValueType<T> && requires {
    requires Table<T>.PrimaryKey.IsAutoInc();
};

}