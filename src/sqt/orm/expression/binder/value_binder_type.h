#pragma once

#include <concepts>
#include <sqt/foundation/statement.h>

namespace sqt {

template<typename T>
concept ValueBinderType = requires(const T t, Statement& statement, const T::ValueType& value) {
    { t.Bind(statement, value) } -> std::same_as<void>;
};

}