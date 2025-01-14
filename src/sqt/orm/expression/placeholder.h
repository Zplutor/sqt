#pragma once

#include <sqt/orm/value_type/bindable_value_type.h>

namespace sqt {

template<BindableValueType V>
struct Placeholder {
    using ValueType = V;
};

template<typename T>
concept PlaceholderType = requires {
    typename T::ValueType;
    requires std::is_same_v<T, Placeholder<typename T::ValueType>>;
};


struct PlaceholderTag {

};

constexpr PlaceholderTag _;

}