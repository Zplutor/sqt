#pragma once

#include <concepts>

namespace sqt {

template<typename T>
concept BinderType = requires {
    typename T::ValueType;
    typename T::ValueTraits;
} &&
requires(const T& t) {
    { t.Index() } -> std::same_as<int>;
};

}