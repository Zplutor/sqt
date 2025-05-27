#pragma once

/**
@file
    Defines the `sqt::LimitSelectCapability<>` class template.
*/

#include <sqt/orm/expression/operand/placeholder.h>
#include <sqt/orm/expression/operand/placeholder_operand.h>
#include <sqt/orm/expression/operand/constant_operand.h>
#include <sqt/orm/querier/selecter/limit_select_decorator.h>
#include <sqt/orm/value/trivial/basic/primitive_value_traits.h>

namespace sqt {

/**
A mixin class template that provides the capability to add a `LIMIT` clause to a selecter.

@tparam SELECTER
    The selecter type that the mixin is applied to. It must satisfy the `sqt::SelecterType` 
    concept.

@details
    This class template provides the `Limit()` methods to the specified selecter type, which create
    instances of `sqt::LimitSelectDecorator<>` that adds a `LIMIT` clause to the SQL statement.

@see sqt::LimitSelectDecorator<>
@see sqt::SelecterType
*/
template<typename SELECTER>
class LimitSelectCapability {
public:
    /**
    Creates a decorator that adds a limit clause with a constant value to the current selecter.

    @param limit
        The limit value to apply. It will be an inline parameter of the decorator.

    @return
        A `sqt::LimitSelectDecorator<>` instance.

    @see sqt::LimitSelectDecorator<>
    */
    constexpr auto Limit(std::size_t limit) const {

        using ValueTraits = PrimitiveValueTraits<std::size_t>;
        using Operand = ConstantOperand<ValueTraits>;

        return LimitSelectDecorator<SELECTER, Operand>{ 
            static_cast<const SELECTER&>(*this), 
            Operand{ limit }
        };
    }

    /**
    Creates a decorator that adds a limit clause with a placeholder to the current selecter.

    @param placeholder
        The placeholder to be used as the limit value in the limit clause.

    @return
        A `sqt::LimitSelectDecorator<>` instance.

    @see sqt::LimitSelectDecorator<>
    @see sqt::Placeholder
    */
    constexpr auto Limit(Placeholder placeholder) const {

        using ValueTraits = PrimitiveValueTraits<std::size_t>;
        using Operand = PlaceholderOperand<ValueTraits>;

        return LimitSelectDecorator<SELECTER, Operand> {
            static_cast<const SELECTER&>(*this),
            Operand{},
        };
    }
};

}