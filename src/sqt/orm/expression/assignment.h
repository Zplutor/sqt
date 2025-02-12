#pragma once

#include <sqt/orm/expression/identifier_operand_like.h>
#include <sqt/orm/expression/value_operand_like.h>

namespace sqt {

template<IdentifierOperandLike IDENTIFIER, ValueOperandLike VALUE>
class Assignment {
public:
    using IdentifierOperandType = IDENTIFIER;
    using ValueOperandType = VALUE;

    static constexpr std::size_t ParameterCount = VALUE::ParameterCount;

    static constexpr auto BuildPlaceholderBinders(int parameter_index) {
        return VALUE::BuildPlaceholderBinders(parameter_index);
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