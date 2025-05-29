#pragma once

/**
@file 
    Defines the `sqt::WhereCapability<>` class template.
*/

#include <sqt/orm/querier/querier_type.h>
#include <sqt/orm/querier/where_decorator.h>

namespace sqt {

/**
A mixin class template that provides the capability to add a `WHERE` clause to a querier.

@tparam QUERIER
    The querier type that the mixin is applied to. It must satisfy the `sqt::QuerierType` concept.

@tparam DECORATOR
    The decorator type that the `Where()` method creates. It defaults to the 
    `sqt::WhereDecorator<>` for non-selecters, or `sqt::WhereSelectDecorator<>` for selecters.

@details
    This class template provides the `Where()` method to the specified querier type, which creates
    instances of the `DECORATOR` that adds a `WHERE` clause to the SQL statement.

@see sqt::QuerierType
@see sqt::WhereDecorator<>
@see sqt::WhereSelectDecorator<>
*/
template<typename QUERIER, template<typename, typename> typename DECORATOR = WhereDecorator>
class WhereCapability {
public:
    /**
    Creates a decorator that adds a `WHERE` clause to the current querier.

    @tparam PREDICATE
        The predicate type that defines the condition for the `WHERE` clause. It must satisfy the
        `sqt::PredicateType` concept.

    @param predicate
        The predicate instance that defines the condition for the `WHERE` clause.

    @return
        A `DECORATOR` instance. It will be a `sqt::WhereDecorator<>` for non-selecters, or a
        `sqt::WhereSelectDecorator<>` for selecters.

    @see sqt::PredicateType
    @see sqt::WhereDecorator<>
    @see sqt::WhereSelectDecorator<>
    */
    template<PredicateType PREDICATE>
    constexpr auto Where(PREDICATE&& predicate) const {

        return DECORATOR<QUERIER, PREDICATE>{
            static_cast<const QUERIER&>(*this),
            std::forward<PREDICATE>(predicate)
        };
    }
};

}