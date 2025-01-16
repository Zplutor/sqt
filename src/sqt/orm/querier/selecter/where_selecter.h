#pragma once

#include <sqt/orm/expression/expression_like.h>
#include <sqt/orm/querier/selecter/limit_capacity.h>
#include <sqt/orm/querier/selecter/selecter_like.h>

namespace sqt {

template<SelecterLike INNER, ExpressionLike EXPR>
class WhereSelecter : 
    public LimitCapacity<WhereSelecter<INNER, EXPR>> {

public:
    static constexpr std::size_t ParameterIndex = INNER::ParameterIndex + INNER::ParameterCount;
    static constexpr std::size_t ParameterCount = EXPR::ParameterCount;

    static constexpr auto BuildPlaceholderBinders() {
        auto inner_binders = INNER::BuildPlaceholderBinders();
        auto expression_binders = EXPR::BuildPlaceholderBinders(ParameterIndex);
        return std::tuple_cat(std::move(inner_binders), std::move(expression_binders));
    }

public:
    constexpr WhereSelecter(INNER inner_selecter, EXPR expression) noexcept :
        inner_selecter_(std::move(inner_selecter)), 
        expression_(std::move(expression)) {

    }

    std::string_view BuildSQL() const {
        static const std::string sql = [this]() {
            return std::format("{} where {}", inner_selecter_.BuildSQL(), expression_.BuildSQL());
        }();
        return sql;
    }

    void BindInlineParameters(Statement& statement) const {
        inner_selecter_.BindInlineParameters(statement);
        expression_.BindInlineParameters(statement, ParameterIndex);
    }

private:
    INNER inner_selecter_;
    EXPR expression_;
};

}