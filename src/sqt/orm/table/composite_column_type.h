#pragma once

#include <concepts>

namespace sqt {

template<typename T>
concept CompositeColumnType = requires {
    typename T::EntityType;
    typename T::ValueType;
    { T::ColumnCount } -> std::same_as<const std::size_t&>;
    requires T::ColumnCount > 0;
};

}