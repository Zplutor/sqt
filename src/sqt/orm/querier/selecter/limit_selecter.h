#pragma once

#include <format>
#include <string>
#include <string_view>
#include <sqt/orm/expression/operand.h>
#include <sqt/orm/expression/placeholder.h>

namespace sqt {

template<typename S, typename O>
class LimitSelecter {
public:
    static constexpr std::size_t ParameterIndex = S::ParameterIndex + S::ParameterCount;
    static constexpr std::size_t ParameterCount = O::ParameterCount;

    static constexpr auto BuildPlaceholderBinders() {

        auto inner_binders = S::BuildPlaceholderBinders();
        auto operand_binder = O::BuildPlaceholderBinder(ParameterIndex);

        return std::tuple_cat(std::move(inner_binders), std::move(operand_binder));
    }

public:
    constexpr LimitSelecter(S inner_selecter, O operand) noexcept : 
        inner_selecter_(std::move(inner_selecter)),
        operand_(std::move(operand)) {

    }

    std::string_view BuildSQL() const {
        static const std::string sql = [this]() {
            return std::format("{} limit {}", inner_selecter_.BuildSQL(), operand_.BuildSQL());
        }();
        return sql;
    }

    void BindInlineParameters(Statement& statement) const {
        operand_.BindInlineParameters(statement, ParameterIndex);
    }

private:
    S inner_selecter_;
    O operand_;
};

}