#pragma once

/**
@file
    Defines the `sqt::Predicate<>` class template.
*/

#include <format>
#include <sqt/orm/expression/predicate_operator.h>
#include <sqt/orm/expression/predicate_term_type.h>

namespace sqt {

/**
Represents a predicate that combines two operands with an operator.

@tparam OPERATOR
    The operator to use for the predicate.

@tparam LHS
    The left-hand side operand of the predicate, which must satisfy the `sqt::PredicateTermType` 
    concept.

@tparam RHS
    The right-hand side operand of the predicate, which must satisfy the `sqt::PredicateTermType` 
    concept.

@details
    This class template satisfies the `sqt::PredicateType` concept.

@see sqt::PredicateOperator
@see sqt::PredicateType
@see sqt::PredicateTermType
*/
template<PredicateOperator OPERATOR, PredicateTermType LHS, PredicateTermType RHS>
class Predicate {
public:
    using LHSOperand = LHS;
    using RHSOperand = RHS;

    static constexpr PredicateOperator Operator = OPERATOR;

    static constexpr std::size_t ParameterCount = LHS::ParameterCount + RHS::ParameterCount;

    static std::string BuildSQL() {
        return std::format(
            "({}){}({})",
            LHS::BuildSQL(),
            PredicateOperatorEnum::ToString(OPERATOR),
            RHS::BuildSQL());
    }

    static constexpr auto BuildPlaceholderBinders(int parameter_index) noexcept {
        auto lhs_binders = LHS::BuildPlaceholderBinders(parameter_index);
        auto rhs_binders = RHS::BuildPlaceholderBinders(parameter_index + LHS::ParameterCount);
        return std::tuple_cat(std::move(lhs_binders), std::move(rhs_binders));
    }

public:
    constexpr Predicate(LHS lhs, RHS rhs) : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {

    }

    template<PredicateType OTHER>
    constexpr auto operator&&(OTHER other) const {
        using ThisType = Predicate<OPERATOR, LHS, RHS>;
        using ResultType = Predicate<PredicateOperator::And, ThisType, OTHER>;
        return ResultType{ *this, std::move(other) };
    }

    template<PredicateType OTHER>
    constexpr auto operator||(OTHER other) const {
        using ThisType = Predicate<OPERATOR, LHS, RHS>;
        using ResultType = Predicate<PredicateOperator::Or, ThisType, OTHER>;
        return ResultType{ *this, std::move(other) };
    }

    void BindInlineParameters(Statement& statement, int parameter_index) const {
        lhs_.BindInlineParameters(statement, parameter_index);
        rhs_.BindInlineParameters(statement, parameter_index + LHS::ParameterCount);
    }

private:
    LHS lhs_{};
    RHS rhs_{};
};

}