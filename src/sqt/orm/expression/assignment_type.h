#pragma once

#include <sqt/orm/expression/assignment_operator.h>
#include <sqt/orm/expression/expression_like.h>

namespace sqt {

template<typename T>
concept AssignmentType = ExpressionLike<T> && requires {
    { T::Operator } -> std::same_as<const AssignmentOperator&>;
};

}