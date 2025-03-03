#pragma once

#include <sqt/orm/expression/expression_like.h>
#include <sqt/orm/expression/predicate_operator.h>

namespace sqt {

template<typename T>
concept PredicateType = ExpressionLike<T> && requires {
    { T::Operator } -> std::same_as<const PredicateOperator&>;
};

}