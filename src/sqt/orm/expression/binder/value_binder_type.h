#pragma once

#include <concepts>

namespace sqt {

template<typename T>
concept ValueBinderType = requires {
    typename T::ValueType;
    typename T::ValueTraits;
} &&
requires(const T& t) {
    { t.GetIndex() } -> std::same_as<int>;
};

}