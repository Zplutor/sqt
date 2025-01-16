#pragma once

#include <concepts>
#include <string>
#include <sqt/core/statement.h>
#include <sqt/orm/binder/binder_chain.h>

namespace sqt {

template<typename T>
concept ExpressionLike = requires(const T t, Statement& statement, int parameter_index) {
    { T::ParameterCount } -> std::same_as<const std::size_t&>;
    { T::BuildPlaceholderBinders(parameter_index) } -> BinderLikeTuple;
    { t.BuildSQL() } -> std::same_as<std::string>;
    { t.BindInlineParameters(statement, parameter_index) } -> std::same_as<void>;
};

}