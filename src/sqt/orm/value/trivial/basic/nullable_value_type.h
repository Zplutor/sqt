#pragma once

/**
@file
    Defines the `sqt::NullableValueType` concept.
*/

#include <optional>
#include <sqt/orm/value/trivial/basic/primitive_value_type.h>

namespace sqt {
/** @cond */
namespace internal {

template<typename T>
struct IsOptional : std::false_type {};

template<typename E>
struct IsOptional<std::optional<E>> : std::true_type {};

template<typename T>
constexpr bool IsOptionalV = IsOptional<T>::value;


template<typename T>
struct GetOptionalValueType {
    using type = void;
};

template<typename E>
struct GetOptionalValueType<std::optional<E>> {
    using type = E;
};

template<typename T>
using GetOptionalValueTypeT = typename GetOptionalValueType<T>::type;

}
/** @endcond */

/**
Constrains a type to be a nullable primitive value type.

@details
    @b Requirements
    - The type must be a `std::optional<>`.
    - The value type of the `std::optional<>` must satisfy the `sqt::PrimitiveValueType` concept.

    Nullable value types are a subset of basic value types, which are constrained by the
    `sqt::BasicValueType` concept.

@see sqt::BasicValueType
@see sqt::PrimitiveValueType
*/
template<typename T>
concept NullableValueType = 
    internal::IsOptionalV<T> && 
    PrimitiveValueType<internal::GetOptionalValueTypeT<T>>;

}