#pragma once

#include <concepts>
#include <sqt/core/statement.h>

namespace sqt {

template<typename T>
concept BinderLike = requires(const T t, Statement& statement, const T::ValueType& value) {
    { t.Bind(statement, value) } -> std::same_as<void>;
};

}