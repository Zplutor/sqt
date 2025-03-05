#pragma once

#include <sqt/orm/expression/expression_creation.h>
#include <sqt/orm/expression/operand/placeholder.h>

#define SQT_PREDICATE_OPERATOR(OP_LITERAL, OP_VALUE, COLUMN_TYPE, VALUE_TYPE) \
friend constexpr auto operator##OP_LITERAL(const COLUMN_TYPE& column, const VALUE_TYPE& value) { \
    return sqt::MakePredicate<sqt::PredicateOperator::OP_VALUE>(column, value); \
} \
friend constexpr auto operator##OP_LITERAL(const VALUE_TYPE& value, const COLUMN_TYPE& column) { \
    return sqt::MakePredicate<sqt::PredicateOperator::OP_VALUE>(value, column); \
} \
friend constexpr auto operator##OP_LITERAL(const COLUMN_TYPE& column, sqt::Placeholder) { \
    auto op1 = sqt::MakeOperand(column); \
    auto op2 = sqt::MakePlaceholderOperand<VALUE_TYPE>(); \
    return sqt::Predicate<sqt::PredicateOperator::OP_VALUE, decltype(op1), decltype(op2)>{ \
        std::move(op1), std::move(op2) \
    }; \
} \
friend constexpr auto operator##OP_LITERAL(sqt::Placeholder, const COLUMN_TYPE& column) { \
    auto op1 = sqt::MakePlaceholderOperand<VALUE_TYPE>(); \
    auto op2 = sqt::MakeOperand(column); \
    return sqt::Predicate<sqt::PredicateOperator::OP_VALUE, decltype(op1), decltype(op2)>{ \
        std::move(op1), std::move(op2) \
    }; \
}


#define __SQT_EXPRESSION_OPERATORS(COLUMN_TYPE, VALUE_TYPE) \
constexpr auto Asc() const { \
    return sqt::MakeOrderingTerm<sqt::Ordering::Ascending>(*this); \
} \
constexpr auto Desc() const { \
    return sqt::MakeOrderingTerm<sqt::Ordering::Descending>(*this); \
} \
constexpr auto operator=(const VALUE_TYPE& value) const { \
    return sqt::MakeAssignment(*this, value); \
} \
SQT_PREDICATE_OPERATOR(==, Equal, COLUMN_TYPE, VALUE_TYPE) \
SQT_PREDICATE_OPERATOR(!=, NotEqual, COLUMN_TYPE, VALUE_TYPE) \
SQT_PREDICATE_OPERATOR(<, Less, COLUMN_TYPE, VALUE_TYPE) \
SQT_PREDICATE_OPERATOR(<=, LessEqual, COLUMN_TYPE, VALUE_TYPE) \
SQT_PREDICATE_OPERATOR(>, Greater, COLUMN_TYPE, VALUE_TYPE) \
SQT_PREDICATE_OPERATOR(>=, GreaterEqual, COLUMN_TYPE, VALUE_TYPE)