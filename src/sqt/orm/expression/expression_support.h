#pragma once

#include <sqt/orm/expression/expression_creation.h>

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
friend constexpr auto operator==(const COLUMN_TYPE& column, const VALUE_TYPE& value) { \
    return sqt::MakePredicate<sqt::PredicateOperator::Equal>(column, value); \
} \
friend constexpr auto operator==(const VALUE_TYPE& value, const COLUMN_TYPE& column) { \
    return sqt::MakePredicate<sqt::PredicateOperator::Equal>(value, column); \
} \
friend constexpr auto operator!=(const COLUMN_TYPE& column, const VALUE_TYPE& value) { \
    return sqt::MakePredicate<sqt::PredicateOperator::NotEqual>(column, value); \
} \
friend constexpr auto operator!=(const VALUE_TYPE& value, const COLUMN_TYPE& column) { \
    return sqt::MakePredicate<sqt::PredicateOperator::NotEqual>(value, column); \
} \
friend constexpr auto operator<(const COLUMN_TYPE& column, const VALUE_TYPE& value) { \
    return sqt::MakePredicate<sqt::PredicateOperator::Less>(column, value); \
} \
friend constexpr auto operator<(const VALUE_TYPE& value, const COLUMN_TYPE& column) { \
    return sqt::MakePredicate<sqt::PredicateOperator::Less>(value, column); \
} \
friend constexpr auto operator<=(const COLUMN_TYPE& column, const VALUE_TYPE& value) { \
    return sqt::MakePredicate<sqt::PredicateOperator::LessEqual>(column, value); \
} \
friend constexpr auto operator<=(const VALUE_TYPE& value, const COLUMN_TYPE& column) { \
    return sqt::MakePredicate<sqt::PredicateOperator::LessEqual>(value, column); \
} \
friend constexpr auto operator>(const COLUMN_TYPE& column, const VALUE_TYPE& value) { \
    return sqt::MakePredicate<sqt::PredicateOperator::Greater>(column, value); \
} \
friend constexpr auto operator>(const VALUE_TYPE& value, const COLUMN_TYPE& column) { \
    return sqt::MakePredicate<sqt::PredicateOperator::Greater>(value, column); \
} \
friend constexpr auto operator>=(const COLUMN_TYPE& column, const VALUE_TYPE& value) { \
    return sqt::MakePredicate<sqt::PredicateOperator::GreaterEqual>(column, value); \
} \
friend constexpr auto operator>=(const VALUE_TYPE& value, const COLUMN_TYPE& column) { \
    return sqt::MakePredicate<sqt::PredicateOperator::GreaterEqual>(value, column); \
}