#pragma once

#include <format>
#include <sqt/orm/expression/expression_like.h>
#include <sqt/orm/expression/operand.h>

namespace sqt {

template<typename LHS, ExpressionLike RHS>
class Assignment {
public:
    static constexpr std::size_t ParameterCount = LHS::ParameterCount + RHS::ParameterCount;

    static constexpr auto BuildPlaceholderBinders(int parameter_index) {
        auto lhs_binders = LHS::BuildPlaceholderBinders(parameter_index);
        auto rhs_binders = RHS::BuildPlaceholderBinders(parameter_index + LHS::ParameterCount);
        return std::tuple_cat(std::move(lhs_binders), std::move(rhs_binders));
    }

public:
    Assignment(LHS lhs, RHS rhs) : lhs_(std::move(lhs)), rhs_(std::move(rhs)) {

    }

    std::string BuildSQL() const {
        return std::format("{}={}", lhs_.BuildSQL(), rhs_.BuildSQL());
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