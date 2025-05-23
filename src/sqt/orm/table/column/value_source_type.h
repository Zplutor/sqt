#pragma once

/**
@file
    Defines the `sqt::ValueSourceType` concept.
*/

#include <concepts>

namespace sqt {

/**
Constrains a type to be a value source type, which is used to retrieve and set values from and to 
entities.

@tparam ENTITY
    The entity type to which the value source type is bound.

@details
    @b Requirements
    - The type must have a nested type `ValueType` that defines the type of the value.
    - The type must have a static method `GetValueFromEntity()` with the following signature:
      @code{.cpp}
      const ValueType& GetValueFromEntity(const ENTITY& entity);
      @endcode
      This method retrieves the value from the entity. The return type is not required to be 
      `const ValueType&`, but it must be convertible to it.
    - The type must have a static method `SetValueToEntity()` with the following signature:
      @code{.cpp}
      void SetValueToEntity(ENTITY& entity, ValueType&& value);
      @endcode
      This method sets the value to the entity. The value is passed as an rvalue reference.

    Value source types are defined as the nested types of columns and composite columns. They 
    encapsulate logic for retrieving and setting values on entities for those columns.

    using `SQT_COLUMN_FIELD` and `SQT_COLUMN_ACCESSOR` macros automatically
    generate value source types that operate on fields or accessors of the entity

    Columns defined using the `SQT_COLUMN_FIELD` and `SQT_COLUMN_ACCESSOR` macros have 
    auto-generated value source types that operate on fields or accessors of the entity. Users can 
    define custom value source types and use the `SQT_COLUMN_CUSTOM` macro to bind them to columns.

@see SQT_COLUMN_ACCESSOR
@see SQT_COLUMN_CUSTOM
@see SQT_COLUMN_FIELD
*/
template<typename T, typename ENTITY>
concept ValueSourceType = 
    requires {
        typename T::ValueType;
    } &&
    requires (const ENTITY& entity) {
        { T::GetValueFromEntity(entity) } -> std::convertible_to<const typename T::ValueType&>;
    } &&
    requires (ENTITY& entity, typename T::ValueType&& value) {
        { T::SetValueToEntity(entity, std::move(value)) } -> std::same_as<void>;
    };

}