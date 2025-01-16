#pragma once

//#include <sqt/orm/expression/assignment.h>
#include <sqt/orm/expression/expression.h>

#define __SQT_EXPRESSION_OPERATORS(COLUMN_TYPE, VALUE_TYPE) \
friend constexpr auto operator==(const COLUMN_TYPE& column, const VALUE_TYPE& value) { \
    return sqt::MakeExpression<sqt::Operator::Equal>(column, value); \
} \
friend constexpr auto operator==(const VALUE_TYPE& value, const COLUMN_TYPE& column) { \
    return sqt::MakeExpression<sqt::Operator::Equal>(value, column); \
} \
friend constexpr auto operator!=(const COLUMN_TYPE& column, const VALUE_TYPE& value) { \
    return sqt::MakeExpression<sqt::Operator::NotEqual>(column, value); \
} \
friend constexpr auto operator!=(const VALUE_TYPE& value, const COLUMN_TYPE& column) { \
    return sqt::MakeExpression<sqt::Operator::NotEqual>(value, column); \
} \
friend constexpr auto operator<(const COLUMN_TYPE& column, const VALUE_TYPE& value) { \
    return sqt::MakeExpression<sqt::Operator::Less>(column, value); \
} \
friend constexpr auto operator<(const VALUE_TYPE& value, const COLUMN_TYPE& column) { \
    return sqt::MakeExpression<sqt::Operator::Less>(value, column); \
} \
friend constexpr auto operator<=(const COLUMN_TYPE& column, const VALUE_TYPE& value) { \
    return sqt::MakeExpression<sqt::Operator::LessEqual>(column, value); \
} \
friend constexpr auto operator<=(const VALUE_TYPE& value, const COLUMN_TYPE& column) { \
    return sqt::MakeExpression<sqt::Operator::LessEqual>(value, column); \
} \
friend constexpr auto operator>(const COLUMN_TYPE& column, const VALUE_TYPE& value) { \
    return sqt::MakeExpression<sqt::Operator::Greater>(column, value); \
} \
friend constexpr auto operator>(const VALUE_TYPE& value, const COLUMN_TYPE& column) { \
    return sqt::MakeExpression<sqt::Operator::Greater>(value, column); \
} \
friend constexpr auto operator>=(const COLUMN_TYPE& column, const VALUE_TYPE& value) { \
    return sqt::MakeExpression<sqt::Operator::GreaterEqual>(column, value); \
} \
friend constexpr auto operator>=(const VALUE_TYPE& value, const COLUMN_TYPE& column) { \
    return sqt::MakeExpression<sqt::Operator::GreaterEqual>(value, column); \
}