#pragma once

#include <sqt/orm/expression/expression_like.h>
#include <sqt/orm/querier/selecter/limit_select_capability.h>
#include <sqt/orm/querier/selecter/order_by_select_capability.h>
#include <sqt/orm/querier/selecter/selecter_type.h>
#include <sqt/orm/querier/where_decorator.h>

namespace sqt {

template<SelecterType SELECTER, ExpressionLike EXPRESSION>
class WhereSelectDecorator : 
    public WhereDecorator<SELECTER, EXPRESSION>,
    public OrderBySelectCapability<WhereSelectDecorator<SELECTER, EXPRESSION>>,
    public LimitSelectCapability<WhereSelectDecorator<SELECTER, EXPRESSION>> {

public:
    using ResultElementType = SELECTER::ResultElementType;

    static ResultElementType GetResultElement(Statement& statement) {
        return SELECTER::GetResultElement(statement);
    }

public:
    using WhereDecorator<SELECTER, EXPRESSION>::WhereDecorator;
};

}