#pragma once

/**
@file
    Defines the `sqt::WhereSelectDecorator<>` class template.
*/

#include <sqt/orm/querier/selecter/limit_select_capability.h>
#include <sqt/orm/querier/selecter/order_by_select_capability.h>
#include <sqt/orm/querier/selecter/selecter_type.h>
#include <sqt/orm/querier/where_decorator.h>

namespace sqt {

/**
A selecter decorator that adds a `WHERE` clause to the SQL statement of the decorated selecter.

@tparam SELECTER
    The selecter type to be decorated, which must satisfy the `sqt::SelecterType` concept.

@tparam PREDICATE
    The predicate type to be applied in the `WHERE` clause. It must satisfy the
    `sqt::PredicateType` concept.

@details
    This decorator extends the `sqt::WhereDecorator<>` to provide specific functionalities for 
    selecters.

    This class template satisfies the `sqt::SelecterType` concept.

@see sqt::PredicateType
@see sqt::SelecterType
@see sqt::WhereDecorator<>
*/
template<SelecterType SELECTER, PredicateType PREDICATE>
class WhereSelectDecorator : 
    public WhereDecorator<SELECTER, PREDICATE>,
    public OrderBySelectCapability<WhereSelectDecorator<SELECTER, PREDICATE>>,
    public LimitSelectCapability<WhereSelectDecorator<SELECTER, PREDICATE>> {

public:
    using ResultElementType = SELECTER::ResultElementType;

    static ResultElementType GetResultElement(Statement& statement) {
        return SELECTER::GetResultElement(statement);
    }

public:
    using WhereDecorator<SELECTER, PREDICATE>::WhereDecorator;
};

}