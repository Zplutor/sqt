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
        typename T::ValueSource;
        { T::Name } -> std::same_as<const std::string_view&>;
    } && 
    requires(Statement& statement, int index, const typename T::EntityType& entity) {
        { T::BindValueFromEntity(statement, index, entity) } -> std::same_as<void>;
    } &&
    requires(const Statement& statement, int index, typename T::EntityType& entity) {
        { T::RetrieveValueToEntity(statement, index, entity) } -> std::same_as<void>;
    };
}