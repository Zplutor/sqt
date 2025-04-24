#pragma once

/**
@file
    Defines the `sqt::PrimitiveValueType` concept.
*/

#include <sqt/orm/value/trivial/basic/primitive_value_traits.h>

namespace sqt {

/**
Constrains a type to be a primitive value type, which refers to a built-in type that can be 
directly mapped to a database data type.

@details
    @b Requirements
    - There must be a `sqt::PrimitiveValueTraits<>` specialization for the type. The specialization
      is defined by the framework.

    The following types are considered primitive value types:
    - Integral types satisfying the `std::integral` concept. These are mapped to 
      `sqt::DataType::Integer`.
    - Floating-point types satisfying the `std::floating_point` concept, excluding `long double`.
      These are mapped to `sqt::DataType::Float`.
    - `std::string`, which is mapped to `sqt::DataType::Text`.

    Primitive value types are not nullable. Refer to the `sqt::NullableValueType` concept for
    nullable value types.

    Primitive value types are a subset of basic value types, which are constrained by the
    `sqt::BasicValueType` concept.

@see sqt::BasicValueType
@see sqt::NullableValueType
@see sqt::PrimitiveValueTraits<>
*/
template<typename T>
concept PrimitiveValueType = requires {
    { PrimitiveValueTraits<T>::DataType };
};

}