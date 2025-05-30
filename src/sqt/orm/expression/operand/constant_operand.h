#pragma once

/**
@file
    Defines the `sqt::ConstantOperand<>` class template.
*/

#include <sqt/orm/internal/parameter_count_deduction.h>
#include <sqt/orm/internal/utility.h>
#include <sqt/orm/value/value_traits_type.h>

namespace sqt {

/**
Represents a constant value operand.

@tparam TRAITS
    The value traits type this operand represents, which must satisfy the `sqt::ValueTraitsType` 
    concept.

@details
    Literals or variables used to create expressions become constant operands. The values are 
    stored in the constant operand, and won't be changed.

    Constant operands in a querier are inline parameters, their values will be bound to the SQL 
    statement by the `BindInlineParameters()` method of the querier before it is executed.

    This class template satisfies the `sqt::ValueOperandType` concept.

@see sqt::ValueOperandType
@see sqt::ValueTraitsType
*/
template<ValueTraitsType TRAITS>
class ConstantOperand {
public:
    using ValueTraits = TRAITS;
    using ValueType = typename TRAITS::ValueType;

    static constexpr std::size_t ParameterCount = internal::ParameterCountForV<TRAITS>;

    static std::string BuildSQL() {
        return internal::JoinPlaceholders(ParameterCount);
    }

    static constexpr std::tuple<> BuildPlaceholderBinders(int parameter_index) noexcept {
        return {};
    }

public:
    constexpr explicit ConstantOperand(ValueType value) : value_(std::move(value)) {

    }

    void BindInlineParameters(Statement& statement, int parameter_index) const {
        ValueTraits::BindValue(statement, parameter_index, value_);
    }

private:
    ValueType value_{};
};

}