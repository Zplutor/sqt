#pragma once

#include <sqt/orm/value/value_traits_type.h>

namespace sqt {

template<typename T>
concept IdentifierValueTraitsType = 
    ValueTraitsType<T> && 
    requires {
        typename T::IdentifierType;
        typename T::EntityType;
    } &&
    requires (Statement& statement, int parameter_index, const typename T::EntityType& entity) {
        { T::BindValueFromEntity(statement, parameter_index, entity) } -> std::same_as<void>;
    } &&
    requires (const Statement& statement, int column_index, typename T::EntityType& entity) {
        { T::RetrieveValueToEntity(statement, column_index, entity) } -> std::same_as<void>;
    };

}