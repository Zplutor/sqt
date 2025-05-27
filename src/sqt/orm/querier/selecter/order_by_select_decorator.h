#pragma once

/**
@file
    Defines the `sqt::OrderBySelectDecorator<>` class template.
*/

#include <format>
#include <sqt/orm/expression/ordering_term_type.h>
#include <sqt/orm/querier/selecter/limit_select_capability.h>
#include <sqt/orm/querier/selecter/selecter_type.h>

namespace sqt {

/**
A selecter decorator that adds an `ORDER BY` clause to the SQL statement of the decorated selecter.

@tparam SELECTER
    The selecter type to be decorated, which must satisfy the `sqt::SelecterType` concept.

@tparam TERMS
    The ordering term types to be applied in the `ORDER BY` clause. Each type must satisfy the
    `sqt::OrderingTermType` concept.

@details
    To create instances of this class template, use the `OrderBy()` method of the
    `sqt::OrderBySelectCapability<>` class template, which is a mixin for selecters that support
    the order by clause.

    This class template satisfies the `sqt::SelecterType` concept.

@see sqt::OrderBySelectCapability<>
@see sqt::OrderingTermType
@see sqt::SelecterType
*/
template<SelecterType SELECTER, OrderingTermType... TERMS>
class OrderBySelectDecorator : 
    public LimitSelectCapability<OrderBySelectDecorator<SELECTER, TERMS...>> {

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
            (build_order_by_clause(TERMS::BuildSQL()), ...);

            return std::format("{} order by {}", SELECTER::BuildSQL(), order_by_clause);
        }();
        return sql;
    }

    static constexpr auto BuildPlaceholderBinders() noexcept {
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