#pragma once

#include <string_view>

namespace sqt {

enum class PredicateOperator {
    Equal,
    NotEqual,
    Less,
    LessEqual,
    Greater,
    GreaterEqual,
    And,
    Or,
};

constexpr std::string_view ConvertPredicateOperatorToString(PredicateOperator op) {
    switch (op) {
    case PredicateOperator::Equal:
        return "=";
    case PredicateOperator::NotEqual:
        return "<>";
    case PredicateOperator::Less:
        return "<";
    case PredicateOperator::LessEqual:
        return "<=";
    case PredicateOperator::Greater:
        return ">";
    case PredicateOperator::GreaterEqual:
        return ">=";
    case PredicateOperator::And:
        return "and";
    case PredicateOperator::Or:
        return "or";
    default:
        return "";
    }
}

}