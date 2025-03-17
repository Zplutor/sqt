#pragma once

#include <concepts>
#include <sqt/foundation/statement.h>

namespace sqt {

template<typename T>
concept ValueTraitsType = 
    requires {
        typename T::ValueType;
    } &&
    requires (Statement& statement, int parameter_index, const typename T::ValueType& value) {
        { T::BindValue(statement, parameter_index, value) } -> std::same_as<void>;
    } &&
    requires (const Statement& statement, int column_index) {
        { T::RetrieveValue(statement, column_index) } -> 
            std::same_as<typename T::ValueType>;
    };
}