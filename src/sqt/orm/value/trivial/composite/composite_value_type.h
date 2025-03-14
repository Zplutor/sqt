#pragma once

#include <tuple>

namespace sqt {

template<typename T>
struct IsCompositeValueType : std::false_type {};

template<typename... T>
struct IsCompositeValueType<std::tuple<T...>> : std::true_type { };


template<typename T>
concept CompositeValueType = IsCompositeValueType<T>::value;

}