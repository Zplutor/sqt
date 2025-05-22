#pragma once

/**
@file
    Defines the `sqt::CompositeColumnType` concept.
*/

#include <concepts>
#include <string>
#include <sqt/orm/table/column/value_source_type.h>

namespace sqt {

/**
Constrains a type to be a composite column type.

@details
    @b Requirements
    - The type must have a nested type `EntityType`, representing the entity type the composite 
      column associates with.
    - The type must have a nested type `ValueType`, representing the value type of the composite 
      column.
    - The type must have a nested type `ValueTraits`, defining traits for the value type.
    - The type must have a nested type `ValueSource`, which must satisfy the `sqt::ValueSourceType`
      concept.
    - The type must have a nested type `ColumnTypes`, which is a tuple of the column types that
      compose the composite column.
    - The type must have a static constant `ColumnCount` of type `std::size_t`, and its value must
      be equal to the number of columns in the composite column.
    - The type must have a static method `BuildColumnNames()` with the following signature:
      @code
      std::string BuildColumnNames()
      @endcode
      This method creates a string containing the names of all columns in the composite column.

    Composite columns are used to group columns together. They can be used to represent keys such
    as primary keys or indexes that consist of one or multiple columns.

    The specializations of the `sqt::CompositeColumn<>` template satisfy this concept.

@see sqt::CompositeColumn<>
@see sqt::CompositeColumn<FIRST, REST...>
@see sqt::CompositeColumn<SINGLE>
@see sqt::ValueSourceType
*/
template<typename T>
concept CompositeColumnType = 
    requires {
        typename T::EntityType;
        typename T::ValueTraits;
        typename T::ValueType;
        typename T::ValueSource;
        typename T::ColumnTypes;
        { T::ColumnCount } -> std::same_as<const std::size_t&>;
        requires T::ColumnCount > 0;
        { T::BuildColumnNames() } -> std::same_as<std::string>;
    } && 
    ValueSourceType<typename T::ValueSource, typename T::EntityType>;

}