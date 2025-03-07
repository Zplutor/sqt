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
} && 
requires (Statement& statement, int parameter_index, const typename T::EntityType& entity) {
    { T::BindValueFromEntity(statement, parameter_index, entity) } -> std::same_as<void>;
} &&
requires (const Statement& statement, int column_index, typename T::EntityType& entity) {
    { T::RetrieveValueToEntity(statement, column_index, entity) } -> std::same_as<void>;
};

}