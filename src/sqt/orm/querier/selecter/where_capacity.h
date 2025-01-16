#pragma once

#include <sqt/orm/expression/expression_like.h>
#include <sqt/orm/querier/selecter/where_selecter.h>

namespace sqt {

template<typename SELECTER>
class WhereCapacity {
public:
    template<ExpressionLike EXPR>
    constexpr auto Where(EXPR expression) const {
        return WhereSelecter<SELECTER, EXPR>{
            static_cast<const SELECTER&>(*this),
            std::move(expression)
        };
    }
};

}