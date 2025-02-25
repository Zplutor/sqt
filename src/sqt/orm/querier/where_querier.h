#pragma once

#include <sqt/orm/expression/expression_like.h>
#include <sqt/orm/querier/querier_like.h>

namespace sqt {

template<QuerierLike QUERIER, ExpressionLike EXPRESSION>
class WhereQuerier {
public:
    static constexpr std::size_t ParameterIndex =
        QUERIER::ParameterIndex + QUERIER::ParameterCount;

    static constexpr std::size_t ParameterCount = EXPRESSION::ParameterCount;

    static std::string_view BuildSQL() {
        static const std::string sql = []() {
            return std::format("{} where {}", QUERIER::BuildSQL(), EXPRESSION::BuildSQL());
        }();
        return sql;
    }

    static constexpr auto BuildPlaceholderBinders() {
        return std::tuple_cat(
            QUERIER::BuildPlaceholderBinders(),
            EXPRESSION::BuildPlaceholderBinders(ParameterIndex));
    }

public:
    constexpr WhereQuerier(QUERIER QUERIER, EXPRESSION expression) :
        querier_(std::move(QUERIER)),
        expression_(std::move(expression)) {

    }

    void BindInlineParameters(Statement& statement) const {
        querier_.BindInlineParameters(statement);
        expression_.BindInlineParameters(statement, ParameterIndex);
    }

private:
    QUERIER querier_;
    EXPRESSION expression_;
};

}