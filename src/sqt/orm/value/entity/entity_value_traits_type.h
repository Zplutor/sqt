#pragma once

/**
@file
    Defines the `sqt::EntityValueTraitsType` concept.
*/

#include <sqt/orm/table/column/column.h>
#include <sqt/orm/value/entity/entity_value_type.h>
#include <sqt/orm/value/value_traits_type.h>

namespace sqt {

/**
Constrains a type to be an entity value traits type, which defines traits for an entity value type.

@details
    @b Requirements
    - The type must satisfy the `sqt::ValueTraitsType` concept.
    - The nested type `ValueType` must satisfy the `sqt::EntityValueType` concept.
    - The type must have a nested type `EntityType`.
    - The type must have a nested type `TableType`, which is the corresponding table type for the
      entity type.
    - The type must have a static constant `ManipulatingColumns` of type 
      `sqt::ColumnsView<EntityType>`, representing the collection of columns the traits type
      manipulates when binding and retrieving values.

    Entity value traits types are used by the framework to interact with entity value types.
    
    There are two kinds of entity value traits types:
    - `sqt::EntireEntityValueTraits<>`, which manipulates the entire entity value, including all 
      columns of the table.
    - `sqt::NoPrimaryKeyEntityValueTraits<>`, which manipulates the entity value excluding columns
      that are part of the primary key.

@see sqt::ColumnsView<>
@see sqt::EntireEntityValueTraits<>
@see sqt::EntityValueType
@see sqt::NoPrimaryKeyEntityValueTraits<>
@see sqt::ValueTraitsType
*/
template<typename T>
concept EntityValueTraitsType = 
    ValueTraitsType<T> && 
    EntityValueType<typename T::ValueType> && 
    requires {
        typename T::EntityType;
        typename T::TableType;
        { T::ManipulatingColumns } -> std::same_as<const ColumnsView<typename T::EntityType>&>;
    };

}