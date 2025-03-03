#pragma once

#include <sqt/orm/expression/assignment.h>
#include <sqt/orm/expression/operand/operand_creation.h>
#include <sqt/orm/expression/ordering.h>
#include <sqt/orm/expression/ordering_term.h>
#include <sqt/orm/expression/predicate.h>

namespace sqt {

template<PredicateOperator OPERATOR, typename LHS, typename RHS>
constexpr auto MakePredicate(LHS&& lhs, RHS&& rhs) {
    auto op1 = MakeOperand(lhs);
    auto op2 = MakeOperand(rhs);
    return Predicate<OPERATOR, decltype(op1), decltype(op2)>{ std::move(op1), std::move(op2) };
}


template<typename LHS, typename RHS>
constexpr auto MakeAssignment(LHS&& lhs, RHS&& rhs) {
    auto value = MakeOperand(rhs);
    return Assignment<decltype(MakeOperand(lhs)), decltype(value)>{ std::move(value) };
}


template<Ordering ORDERING, typename IDENTIFIER>
constexpr auto MakeOrderingTerm(IDENTIFIER&& identifier) {
    return OrderingTerm<ORDERING, decltype(MakeOperand(identifier))>{};
}

}