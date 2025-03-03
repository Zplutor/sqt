#pragma once

#include <sqt/orm/expression/expression_like.h>
#include <sqt/orm/expression/ordering.h>

namespace sqt {

template<typename T>
concept OrderingTermType = ExpressionLike<T> && requires {
    { T::OrderingValue } -> std::same_as<const Ordering&>;
};

}
