#pragma once

/**
@file
    Defines the `sqt::OrderBySelectCapability<>` class template.
*/

#include <sqt/orm/querier/selecter/order_by_select_decorator.h>

namespace sqt {

/**
A mixin class template that provides the capability to add an `ORDER BY` clause to a selecter.

@tparam SELECTER
    The selecter type that the mixin is applied to. It must satisfy the `sqt::SelecterType`
    concept.

@details
    This class template provides the `OrderBy()` method to the specified selecter type, which
    create an instances of `sqt::OrderBySelectDecorator<>` that adds an `ORDER BY` clause to the 
    SQL statement.

@see sqt::OrderBySelectDecorator<>
@see sqt::SelecterType
*/
template<typename SELECTER>
class OrderBySelectCapability {
public:
    /**
    Creates a decorator that adds an `ORDER BY` clause to the current selecter.

    @tparam TERMS
        The ordering term types to be used in the `ORDER BY` clause. Each type must satisfy the 
        `sqt::OrderingTermType` concept.

    @param terms
        The ordering term instances. They are only used to deduce the types.

    @return
        A `sqt::OrderBySelectDecorator<>` instance.

    @see sqt::OrderBySelectDecorator<>
    @see sqt::OrderingTermType
    */
    template<OrderingTermType... TERMS>
    constexpr auto OrderBy(const TERMS&... terms) const {
        return OrderBySelectDecorator<SELECTER, TERMS...>{
            static_cast<const SELECTER&>(*this)
        };
    }
};

}