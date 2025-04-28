#pragma once

/**
@file
    Defines the `sqt::ColumnType` concept.
*/

#include <concepts>
#include <sqt/orm/table/column/abstract_column.h>
#include <sqt/orm/table/column/value_source_type.h>

namespace sqt {

/**
Constrains a type to be a column type.

@details
    @b Requirements
    - The type must derive from `sqt::AbstractColumn`.
    - The type must have a nested type `EntityType`, representing the entity type from which the 
      column is mapped.
    - The type must have a nested type `ValueType`, representing the value type of the column.
    - The type must have a nested type `ValueTraits`, defining traits for the value type.
    - The type must have a nested type `ValueSource`, which must satisfy the `sqt::ValueSourceType`
      concept.
    - The type must have a static constant `Name` of type `std::string_view`.

    Columns defined by the `SQT_COLUMN_FIELD`, `SQT_COLUMN_ACCESSOR` and `SQT_COLUMN_CUSTOM` macros
    satisfy this concept.

@see sqt::AbstractColumn
@see sqt::ValueSourceType
@see SQT_COLUMN_ACCESSOR
@see SQT_COLUMN_CUSTOM
@see SQT_COLUMN_FIELD
*/
template<typename T>
concept ColumnType = 
    std::is_base_of_v<AbstractColumn, T> && 
    requires {
        typename T::EntityType;
        typename T::ValueType;
        typename T::ValueTraits;
        typename T::ValueSource;
        { T::Name } -> std::same_as<const std::string_view&>;
    } && 
    ValueSourceType<typename T::ValueSource, typename T::EntityType>;
}