#pragma once

/**
@file
    Defines the `sqt::BasicValueTraitsType` concept.
*/

#include <concepts>
#include <sqt/foundation/data_type.h>
#include <sqt/orm/value/value_traits_type.h>

namespace sqt {

/**
Constrains a type to be a basic value traits type, which defines traits for a basic value type.

@details
    @b Requirements
    - The type must satisfy the `sqt::ValueTraitsType` concept.
    - The type must have a static constant `DataType` of type `sqt::DataType`.
    - The type must have a static constant `IsNullable` of type `bool`.

    Basic value traits types are used by the framework to interact with basic value types. The data
    type and nullability of a column are determined by the corrsponding basic value traits type.

    There are three kinds of basic value traits types:
    - `sqt::PrimitiveValueTraits<>`, for primitive value types, defined by the framework.
    - `sqt::NullableValueTraits<>`, for nullable value types, which adds nullability to primitive 
      value traits types.
    - `sqt::CustomValueTraits<>`, for custom value types, defined by the user.

@see sqt::BasicValueType
@see sqt::CustomValueTraits<>
@see sqt::NullableValueTraits<>
@see sqt::PrimitiveValueTraits<>
@see sqt::ValueTraitsType
*/
template<typename T>
concept BasicValueTraitsType = ValueTraitsType<T> && requires {
    { T::DataType } -> std::same_as<const DataType&>;
    { T::IsNullable } -> std::same_as<const bool&>;
};

}