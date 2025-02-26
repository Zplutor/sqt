#pragma once

#include <format>
#include <sqt/orm/expression/operand/identifier_operand_type.h>
#include <sqt/orm/expression/operand/value_operand_type.h>
#include <sqt/orm/expression/operator.h>

namespace sqt {

template<IdentifierOperandType IDENTIFIER, ValueOperandType VALUE>
class Assignment {
public:
    using LHSOperand = IDENTIFIER;
    using RHSOperand = VALUE;

    static constexpr AssignmentOperator Operator = AssignmentOperator::Assign;

    static constexpr std::size_t ParameterCount = VALUE::ParameterCount;

    static constexpr auto BuildPlaceholderBinders(int parameter_index) {
        return VALUE::BuildPlaceholderBinders(parameter_index);
    }

    static std::string BuildSQL() {
        return std::format("{}={}", LHSOperand::BuildSQL(), RHSOperand::BuildSQL());
    }

public:
    constexpr explicit Assignment(VALUE value) : value_(std::move(value)) {

    }

    void BindInlineParameters(Statement& statement, int parameter_index) const {
        value_.BindInlineParameters(statement, parameter_index);
    }

private:
    VALUE value_{};
};

}