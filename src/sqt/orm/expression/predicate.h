#pragma once

#include <format>
#include <sqt/orm/expression/predicate_operator.h>
#include <sqt/orm/expression/predicate_term_type.h>

namespace sqt {

template<PredicateOperator OPERATOR, PredicateTermType LHS, PredicateTermType RHS>
class Predicate {
public:
    static constexpr PredicateOperator Operator = OPERATOR;

    static constexpr std::size_t ParameterCount = LHS::ParameterCount + RHS::ParameterCount;

    static std::string BuildSQL() {
        return std::format(
            "({}){}({})",
            LHS::BuildSQL(),
            ConvertPredicateOperatorToString(OPERATOR),
            RHS::BuildSQL());
    }

    static constexpr auto BuildPlaceholderBinders(int parameter_index) {
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