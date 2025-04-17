#pragma once

#include <concepts>
#include <sqt/foundation/statement.h>
#include <sqt/orm/expression/binder/binder_chain.h>
#include <sqt/orm/expression/binder/binder_tuple_type.h>

namespace sqt {

template<typename T>
concept QuerierType = 
    requires {
        { T::ParameterIndex } -> std::same_as<const std::size_t&>;
        requires T::ParameterIndex >= 1;
        { T::ParameterCount } -> std::same_as<const std::size_t&>;
        { T::BuildSQL() } -> std::same_as<std::string_view>;
        { T::BuildPlaceholderBinders() } -> BinderTupleType;
    } 
    &&
    requires(const T t, Statement& statement) {
        { t.BindInlineParameters(statement) } -> std::same_as<void>;
    };

}