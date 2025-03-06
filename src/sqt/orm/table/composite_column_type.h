#pragma once

#include <concepts>
#include <string>

namespace sqt {

template<typename T>
concept CompositeColumnType = requires {
    typename T::EntityType;
    typename T::ValueType;
    typename T::ValueTraits;
    { T::ColumnCount } -> std::same_as<const std::size_t&>;
    requires T::ColumnCount > 0;
    { T::BuildColumnNames() } -> std::same_as<std::string>;
};

}