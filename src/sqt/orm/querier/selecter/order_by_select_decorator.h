#pragma once

#include <format>
#include <sqt/orm/expression/ordering_term_type.h>
#include <sqt/orm/querier/selecter/limit_select_capability.h>
#include <sqt/orm/querier/selecter/selecter_type.h>

namespace sqt {

template<SelecterType SELECTER, OrderingTermType... TERM>
class OrderBySelectDecorator : 
    public LimitSelectCapability<OrderBySelectDecorator<SELECTER, TERM...>> {

public:
    using ResultElementType = SELECTER::ResultElementType;

    static constexpr std::size_t ParameterIndex =
        SELECTER::ParameterIndex + SELECTER::ParameterCount;

    static constexpr std::size_t ParameterCount = 0;

    static std::string_view BuildSQL() {
        static const std::string sql = []() {
        
            std::string order_by_clause;
            int index{};
            auto build_order_by_clause = [&order_by_clause, &index](const std::string& sql) {
                if (index != 0) {
                    order_by_clause += ',';
                }
                order_by_clause += sql;
                ++index;
            };
            (build_order_by_clause(TERM::BuildSQL()), ...);

            return std::format("{} order by {}", SELECTER::BuildSQL(), order_by_clause);
        }();
        return sql;
    }

    static constexpr auto BuildPlaceholderBinders() {
        return std::tuple<>{};
    }

    static ResultElementType GetResultElement(Statement& statement) {
        return SELECTER::GetResultElement(statement);
    }

public:
    constexpr explicit OrderBySelectDecorator(SELECTER selecter) noexcept : 
        selecter_(std::move(selecter)) {

    }

    void BindInlineParameters(Statement& statement) const {
        selecter_.BindInlineParameters(statement);
    }

private:
    SELECTER selecter_;
};

}