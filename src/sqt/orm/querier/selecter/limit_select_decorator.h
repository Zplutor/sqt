#pragma once

#include <format>
#include <string>
#include <string_view>
#include <sqt/orm/expression/operand/value_operand_type.h>
#include <sqt/orm/querier/selecter/selecter_type.h>

namespace sqt {

template<SelecterType SELECTER, ValueOperandType OPERAND>
class LimitSelectDecorator {
public:
    using ResultElementType = SELECTER::ResultElementType;

    static constexpr std::size_t ParameterIndex = 
        SELECTER::ParameterIndex + SELECTER::ParameterCount;

    static constexpr std::size_t ParameterCount = OPERAND::ParameterCount;

    static std::string_view BuildSQL() {
        static const std::string sql = std::format(
            "{} limit {}", 
            SELECTER::BuildSQL(), 
            OPERAND::BuildSQL());
        return sql;
    }

    static constexpr auto BuildPlaceholderBinders() {
        return std::tuple_cat(
            SELECTER::BuildPlaceholderBinders(), 
            OPERAND::BuildPlaceholderBinders(ParameterIndex));
    }

    static ResultElementType GetResultElement(Statement& statement) {
        return SELECTER::GetResultElement(statement);
    }

public:
    constexpr LimitSelectDecorator(SELECTER selecter, OPERAND operand) noexcept :
        selecter_(std::move(selecter)),
        operand_(std::move(operand)) {

    }

    void BindInlineParameters(Statement& statement) const {
        selecter_.BindInlineParameters(statement);
        operand_.BindInlineParameters(statement, ParameterIndex);
    }

private:
    SELECTER selecter_;
    OPERAND operand_;
};

}