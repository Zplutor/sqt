#pragma once

#include <sqt/orm/value/nullable_value_type.h>

namespace sqt {

template<typename... T>
struct AreAllPrimitiveOrNullableValueTypes : std::false_type {};

template<>
struct AreAllPrimitiveOrNullableValueTypes<> : std::true_type {};

template<typename T, typename... Rest>
struct AreAllPrimitiveOrNullableValueTypes<T, Rest...> {
    static constexpr bool value =
        (PrimitiveValueType<T> || NullableValueType<T>) &&
        AreAllPrimitiveOrNullableValueTypes<Rest...>::value;
};


template<typename T>
struct IsCompositeValueType : std::false_type {};

template<typename... Types>
struct IsCompositeValueType<std::tuple<Types...>> {
    static constexpr bool value = AreAllPrimitiveOrNullableValueTypes<Types...>::value;
};


template<typename T>
concept CompositeValueType = IsCompositeValueType<T>::value;

}