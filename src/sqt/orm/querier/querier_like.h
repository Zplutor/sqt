#pragma once

#include <concepts>
#include <sqt/foundation/statement.h>
#include <sqt/orm/binder/binder_chain.h>

namespace sqt {

template<typename T>
concept QuerierLike = 
    requires {
        { T::ParameterIndex } -> std::same_as<const std::size_t&>;
        { T::ParameterCount } -> std::same_as<const std::size_t&>;
        { T::BuildSQL() } -> std::same_as<std::string_view>;
        { T::BuildPlaceholderBinders() } -> BinderLikeTuple;
    } 
    &&
    requires(const T t, Statement& statement) {
        { t.BindInlineParameters(statement) } -> std::same_as<void>;
    };

}