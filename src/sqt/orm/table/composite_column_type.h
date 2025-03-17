#pragma once

#include <concepts>
#include <string>

namespace sqt {

template<typename T>
concept CompositeColumnType = 
    requires {
        typename T::EntityType;
        typename T::ValueTraits;
        typename T::ValueType;
        typename T::ValueSource;
        { T::ColumnCount } -> std::same_as<const std::size_t&>;
        requires T::ColumnCount > 0;
        { T::BuildColumnNames() } -> std::same_as<std::string>;
    } && 
    requires (Statement& statement, int index, const typename T::EntityType& entity) {
        { T::BindValueFromEntity(statement, index, entity) } -> std::same_as<void>;
    } &&
    requires (const Statement& statement, int index, typename T::EntityType& entity) {
        { T::RetrieveValueToEntity(statement, index, entity) } -> std::same_as<void>;
    };

}