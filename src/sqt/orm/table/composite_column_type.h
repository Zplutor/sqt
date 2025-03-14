#pragma once

#include <concepts>
#include <string>

namespace sqt {

template<typename T>
concept CompositeColumnType = 
    requires {
        typename T::Descriptor;
        { T::ColumnCount } -> std::same_as<const std::size_t&>;
        requires T::ColumnCount > 0;
        { T::BuildColumnNames() } -> std::same_as<std::string>;
    } && 
    requires (Statement& statement, int index, const typename T::Descriptor::EntityType& entity) {
        { T::BindValueFromEntity(statement, index, entity) } -> std::same_as<void>;
    } &&
    requires (const Statement& statement, int index, typename T::Descriptor::EntityType& entity) {
        { T::RetrieveValueToEntity(statement, index, entity) } -> std::same_as<void>;
    };

}