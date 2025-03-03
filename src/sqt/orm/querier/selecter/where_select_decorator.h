#pragma once

#include <sqt/orm/querier/selecter/limit_select_capability.h>
#include <sqt/orm/querier/selecter/order_by_select_capability.h>
#include <sqt/orm/querier/selecter/selecter_type.h>
#include <sqt/orm/querier/where_decorator.h>

namespace sqt {

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