#pragma once

/**
@file
    Defines the `sqt::PlaceholderOperand<>` class template.
*/

#include <sqt/orm/expression/binder/binder.h>
#include <sqt/orm/internal/parameter_count_deduction.h>
#include <sqt/orm/internal/utility.h>
#include <sqt/orm/value/value_traits_type.h>

namespace sqt {

/**
Represents a placeholder operand in an expression.

@tparam TRAITS
    The value traits type the placeholder represents, which must satisfy the `sqt::ValueTraitsType`
    concept.

@details
    When using the `sqt::_` constant to create an expression, a placeholder operand is created. A
    placeholder operand does not store any value, and it creates a binder by the 
    `BuildPlaceholderBinders()` method for users to bind values at the specified parameter index. 
    The bindings of placeholders in a querier is done by the `BeginBindings()` method of the 
    `sqt::Executor<>` class template.

    This class template satisfies the `sqt::ValueOperandType` concept.

@see sqt::Executor<>::BeginBindings()
@see sqt::ValueOperandType
@see sqt::ValueTraitsType
@see sqt::_
*/
template<ValueTraitsType TRAITS>
class PlaceholderOperand {
public:
    using ValueTraits = TRAITS;
    using ValueType = typename TRAITS::ValueType;

    static constexpr std::size_t ParameterCount = internal::ParameterCountForV<TRAITS>;

    static std::string BuildSQL() {
        return std::format("{}", internal::JoinPlaceholders(ParameterCount));
    }

    static constexpr auto BuildPlaceholderBinders(int parameter_index) noexcept {
        return std::make_tuple(Binder<ValueTraits>{ parameter_index });
    }

public:
    constexpr PlaceholderOperand() noexcept = default;

    constexpr void BindInlineParameters(Statement& statement, int parameter_index) const noexcept {

    }
};

}