#pragma once

#include <sqt/orm/expression/assignment.h>
#include <sqt/orm/expression/expression.h>
#include <sqt/orm/expression/operand/operand_creation.h>
#include <sqt/orm/expression/operator.h>

namespace sqt {

template<Operator OPERATOR, typename LHS, typename RHS>
constexpr auto MakeExpression(LHS&& lhs, RHS&& rhs) {

    auto op1 = MakeOperand(lhs);
    auto op2 = MakeOperand(rhs);

    return Expression<OPERATOR, decltype(op1), decltype(op2)>{ std::move(op1), std::move(op2) };
}


template<typename LHS, typename RHS>
constexpr auto MakeAssignment(LHS&& lhs, RHS&& rhs) {

    auto value = MakeOperand(rhs);
    return Assignment<decltype(MakeOperand(lhs)), decltype(value)>{ std::move(value) };
}

}