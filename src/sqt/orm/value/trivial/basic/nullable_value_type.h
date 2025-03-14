#pragma once

#include <optional>
#include <sqt/orm/value/trivial/basic/primitive_value_type.h>

namespace sqt {

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


template<typename T>
concept NullableValueType = IsOptionalV<T> && PrimitiveValueType<GetOptionalValueTypeT<T>>;

}