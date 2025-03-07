#pragma once

#include <concepts>
#include <sqt/foundation/statement.h>
#include <sqt/orm/table/abstract_column.h>

namespace sqt {

template<typename T>
concept ColumnType = 
    std::is_base_of_v<AbstractColumn, T> && 
    requires {
        typename T::EntityType;
        typename T::ValueType;
        typename T::ValueTraits;
        { T::Name } -> std::same_as<const std::string_view&>;
    } && 
    requires (Statement& statement, int parameter_index, const typename T::EntityType& entity) {
        { T::BindValueFromEntity(statement, parameter_index, entity) } -> std::same_as<void>;
    } &&
    requires (const Statement& statement, int column_index, typename T::EntityType& entity) {
        { T::RetrieveValueToEntity(statement, column_index, entity) } -> std::same_as<void>;
    };
}