#pragma once

#include <concepts>
#include <string>
#include <sqt/foundation/statement.h>
#include <sqt/orm/expression/binder/value_binder_chain.h>

namespace sqt {

template<typename T>
concept ExpressionLike = requires(const T t, Statement& statement, int parameter_index) {
    { T::ParameterCount } -> std::same_as<const std::size_t&>;
    { T::BuildPlaceholderBinders(parameter_index) } -> BinderLikeTuple;
    { T::BuildSQL() } -> std::same_as<std::string>;
    { t.BindInlineParameters(statement, parameter_index) } -> std::same_as<void>;
};

}