#pragma once

/**
@file 
    Defines the `sqt::Assignment<>` class template.
*/

#include <format>
#include <sqt/orm/expression/assignment_operator.h>
#include <sqt/orm/expression/operand/identifier_operand_type.h>
#include <sqt/orm/expression/operand/value_operand_type.h>

namespace sqt {

/**
Represents an assignment of a value to an identifier.

@tparam IDENTIFIER
    The identifier operand type, which must satisfy the `sqt::IdentifierOperandType` concept.

@tparam VALUE
    The value operand type, which must satisfy the `sqt::ValueOperandType` concept.

@details
    This class template satisfies the `sqt::AssignmentType` concept.

@see sqt::AssignmentType
@see sqt::IdentifierOperandType
@see sqt::ValueOperandType
*/
template<IdentifierOperandType IDENTIFIER, ValueOperandType VALUE>
class Assignment {
public:
    using LHSOperand = IDENTIFIER;
    using RHSOperand = VALUE;

    static constexpr AssignmentOperator Operator = AssignmentOperator::Assign;

    static constexpr std::size_t ParameterCount = VALUE::ParameterCount;

    static constexpr auto BuildPlaceholderBinders(int parameter_index) noexcept {
        return VALUE::BuildPlaceholderBinders(parameter_index);
    }

    static std::string BuildSQL() {
        return std::format("{}={}", LHSOperand::BuildSQL(), RHSOperand::BuildSQL());
    }

public:
    constexpr explicit Assignment(VALUE value) noexcept : value_(std::move(value)) {

    }

    void BindInlineParameters(Statement& statement, int parameter_index) const {
        value_.BindInlineParameters(statement, parameter_index);
    }

private:
    VALUE value_{};
};

}