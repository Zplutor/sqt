#pragma once

#include <concepts>
#include <sqt/foundation/statement.h>
#include <sqt/orm/table/abstract_column.h>
#include <sqt/orm/table/column/column_descriptor_type.h>

namespace sqt {

template<typename T>
concept ColumnType = 
    std::is_base_of_v<AbstractColumn, T> && 
    requires {
        typename T::Descriptor;
        typename T::EntityType;
        typename T::ValueType;
        typename T::ValueTraits;
        { T::Name } -> std::same_as<const std::string_view&>;
    } && 
    ColumnDescriptorType<typename T::Descriptor> &&
    requires(Statement& statement, int index, const typename T::EntityType& entity) {
        { T::BindValueFromEntity(statement, index, entity) } -> std::same_as<void>;
    } &&
    requires(const Statement& statement, int index, typename T::EntityType& entity) {
        { T::RetrieveValueToEntity(statement, index, entity) } -> std::same_as<void>;
    };
}