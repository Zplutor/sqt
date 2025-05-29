#pragma once

/**
@file
    Defines the `sqt::PredicateOperator` enum.
*/

#include <string_view>

namespace sqt {

/**
Represents the operators used in predicates.
*/
enum class PredicateOperator {

    /**
    Equal operator.
    */
    Equal,

    /**
    Not equal operator.
    */
    NotEqual,

    /**
    Less operator.
    */
    Less,

    /**
    Less equal operator.
    */
    LessEqual,

    /**
    Greater operator.
    */
    Greater,

    /**
    Greater equal operator.
    */
    GreaterEqual,

    /**
    Logical AND operator.
    */
    And,

    /**
    Logical OR operator.
    */
    Or,
};


/**
Provides utility functions for working with the `sqt::PredicateOperator` enum.

@see sqt::PredicateOperator
*/
class PredicateOperatorEnum {
public:
    /**
    Converts the specified `sqt::PredicateOperator` value to the corresponding string in SQL 
    syntax.

    @param op
        The value to be converted.

    @return
        The string representation of the specified value.

    @details
        The conversion follows the following mapping:
        |Operator                              |String|
        |--------------------------------------|------|
        |`sqt::PredicateOperator::Equal`       |`=`   |
        |`sqt::PredicateOperator::NotEqual`    |`<>`  |
        |`sqt::PredicateOperator::Less`        |`<`   |
        |`sqt::PredicateOperator::LessEqual`   |`<=`  |
        |`sqt::PredicateOperator::Greater`     |`>`   |
        |`sqt::PredicateOperator::GreaterEqual`|`>=`  |
        |`sqt::PredicateOperator::And`         |`and` |
        |`sqt::PredicateOperator::Or`          |`or`  |
    */
    static constexpr std::string_view ToString(PredicateOperator op) noexcept {
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

public:
    PredicateOperatorEnum() = delete;
};

}