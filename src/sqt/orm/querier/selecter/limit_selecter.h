#pragma once

#include <format>
#include <string>
#include <string_view>
#include <sqt/orm/expression/expression_like.h>
#include <sqt/orm/expression/operand.h>
#include <sqt/orm/expression/placeholder.h>
#include <sqt/orm/querier/selecter/selecter_like.h>

namespace sqt {

template<SelecterLike INNER, ExpressionLike EXPR>
class LimitSelecter {
public:
    using ResultElementType = INNER::ResultElementType;

    static constexpr std::size_t ParameterIndex = INNER::ParameterIndex + INNER::ParameterCount;
    static constexpr std::size_t ParameterCount = EXPR::ParameterCount;

    static std::string_view BuildSQL() {
        static const std::string sql = std::format(
            "{} limit {}", 
            INNER::BuildSQL(), 
            EXPR::BuildSQL());
        return sql;
    }

    static constexpr auto BuildPlaceholderBinders() {
        auto inner_binders = INNER::BuildPlaceholderBinders();
        auto expression_binders = EXPR::BuildPlaceholderBinders(ParameterIndex);
        return std::tuple_cat(std::move(inner_binders), std::move(expression_binders));
    }

    static ResultElementType GetResultElement(Statement& statement) {
        return INNER::GetResultElement(statement);
    }

public:
    constexpr LimitSelecter(INNER inner_selecter, EXPR expression) noexcept :
        inner_selecter_(std::move(inner_selecter)),
        expression_(std::move(expression)) {

    }

    void BindInlineParameters(Statement& statement) const {
        expression_.BindInlineParameters(statement, ParameterIndex);
    }

private:
    INNER inner_selecter_;
    EXPR expression_;
};

}