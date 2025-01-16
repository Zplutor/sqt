#pragma once

#include <format>
#include <sqt/orm/expression/expression_like.h>
#include <sqt/orm/expression/operand.h>
#include <sqt/orm/expression/operator.h>

namespace sqt {

template<Operator OP, ExpressionLike LHS, ExpressionLike RHS>
class Expression {
public:
    static constexpr std::size_t ParameterCount = LHS::ParameterCount + RHS::ParameterCount;

    static constexpr auto BuildPlaceholderBinders(int parameter_index) {
        auto lhs_binders = LHS::BuildPlaceholderBinders(parameter_index);
        auto rhs_binders = RHS::BuildPlaceholderBinders(parameter_index + LHS::ParameterCount);
        return std::tuple_cat(std::move(lhs_binders), std::move(rhs_binders));
    }

public:
    constexpr Expression(LHS lhs, RHS rhs) : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {

    }

    template<ExpressionLike Other>
    auto operator&&(Other other) const {
        using ThisType = Expression<OP, LHS, RHS>;
        using ResultType = Expression<Operator::And, ThisType, Other>;
        return ResultType{ *this, std::move(other) };
    }

    template<ExpressionLike Other>
    auto operator||(Other other) const {
        using ThisType = Expression<OP, LHS, RHS>;
        using ResultType = Expression<Operator::Or, ThisType, Other>;
        return ResultType{ *this, std::move(other) };
    }

    std::string BuildSQL() const {
        return std::format(
            "({}{}{})",
            lhs_.BuildSQL(), 
            ConvertOperatorToString(OP),
            rhs_.BuildSQL());
    }

    void BindInlineParameters(Statement& statement, int parameter_index) const {
        lhs_.BindInlineParameters(statement, parameter_index);
        rhs_.BindInlineParameters(statement, parameter_index + LHS::ParameterCount);
    }

private:
    LHS lhs_{};
    RHS rhs_{};
};


template<Operator Operator, typename Operand1, typename Operand2>
constexpr auto MakeExpression(Operand1&& op1, Operand2&& op2) {
    using LHS = Operand<std::decay_t<Operand1>>;
    using RHS = Operand<std::decay_t<Operand2>>;
    return Expression<Operator, LHS, RHS>{
        LHS{ std::forward<Operand1>(op1) },
        RHS{ std::forward<Operand2>(op2) },
    };
}

}