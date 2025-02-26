#pragma once

#include <sqt/orm/expression/expression_like.h>
#include <sqt/orm/expression/operator.h>

namespace sqt {

template<typename T>
concept AssignmentType = ExpressionLike<T> && requires {
    { T::Operator } -> std::same_as<const AssignmentOperator&>;
};

}