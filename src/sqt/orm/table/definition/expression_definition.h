#pragma once

#include <sqt/orm/expression/assignment.h>
#include <sqt/orm/expression/operand/constant_operand.h>
#include <sqt/orm/expression/operand/identifier_operand.h>
#include <sqt/orm/expression/operand/placeholder.h>
#include <sqt/orm/expression/operand/placeholder_operand.h>
#include <sqt/orm/expression/ordering.h>
#include <sqt/orm/expression/ordering_term.h>
#include <sqt/orm/expression/predicate.h>
#include <sqt/orm/value/identifier/identifier_value_traits.h>

#define SQT_PREDICATE_OPERATOR(OPERATOR, OP_VALUE, COLUMN_TYPE) \
friend constexpr auto OPERATOR( \
    const COLUMN_TYPE& column, \
    const typename COLUMN_TYPE::ValueType& value) { \
    using LHS = sqt::IdentifierOperand<COLUMN_TYPE>; \
    using RHS = sqt::ConstantOperand<typename COLUMN_TYPE::ValueTraits>; \
    return sqt::Predicate<sqt::PredicateOperator::OP_VALUE, LHS, RHS>{ LHS{}, RHS{ value } }; \
} \
friend constexpr auto OPERATOR( \
    const typename COLUMN_TYPE::ValueType& value, \
    const COLUMN_TYPE& column) { \
    using LHS = sqt::ConstantOperand<typename COLUMN_TYPE::ValueTraits>; \
    using RHS = sqt::IdentifierOperand<COLUMN_TYPE>; \
    return sqt::Predicate<sqt::PredicateOperator::OP_VALUE, LHS, RHS>{ LHS{ value }, RHS{} }; \
} \
friend constexpr auto OPERATOR(const COLUMN_TYPE& column, sqt::Placeholder) { \
    using LHS = sqt::IdentifierOperand<COLUMN_TYPE>; \
    using RHS = sqt::PlaceholderOperand<sqt::IdentifierValueTraits<COLUMN_TYPE>>; \
    return sqt::Predicate<sqt::PredicateOperator::OP_VALUE, LHS, RHS>{ LHS{}, RHS{} }; \
} \
friend constexpr auto OPERATOR(sqt::Placeholder, const COLUMN_TYPE& column) { \
    using LHS = sqt::PlaceholderOperand<sqt::IdentifierValueTraits<COLUMN_TYPE>>; \
    using RHS = sqt::IdentifierOperand<COLUMN_TYPE>; \
    return sqt::Predicate<sqt::PredicateOperator::OP_VALUE, LHS, RHS>{ LHS{}, RHS{} }; \
}


#define __SQT_EXPRESSION_OPERATORS(COLUMN_TYPE) \
constexpr auto Asc() const { \
    return sqt::OrderingTerm<sqt::Ordering::Ascending, sqt::IdentifierOperand<COLUMN_TYPE>>{}; \
} \
constexpr auto Desc() const { \
    return sqt::OrderingTerm<sqt::Ordering::Descending, sqt::IdentifierOperand<COLUMN_TYPE>>{}; \
} \
constexpr auto operator=(const typename COLUMN_TYPE::ValueType& value) const { \
    using LHS = sqt::IdentifierOperand<COLUMN_TYPE>; \
    using RHS = sqt::ConstantOperand<typename COLUMN_TYPE::ValueTraits>; \
    return sqt::Assignment<LHS, RHS>{ RHS{ value } }; \
} \
constexpr auto operator=(sqt::Placeholder) const { \
    using LHS = sqt::IdentifierOperand<COLUMN_TYPE>; \
    using RHS = sqt::PlaceholderOperand<sqt::IdentifierValueTraits<COLUMN_TYPE>>; \
    return sqt::Assignment<LHS, RHS>{ RHS{} }; \
} \
SQT_PREDICATE_OPERATOR(operator==, Equal, COLUMN_TYPE) \
SQT_PREDICATE_OPERATOR(operator!=, NotEqual, COLUMN_TYPE) \
SQT_PREDICATE_OPERATOR(operator<, Less, COLUMN_TYPE) \
SQT_PREDICATE_OPERATOR(operator<=, LessEqual, COLUMN_TYPE) \
SQT_PREDICATE_OPERATOR(operator>, Greater, COLUMN_TYPE) \
SQT_PREDICATE_OPERATOR(operator>=, GreaterEqual, COLUMN_TYPE)