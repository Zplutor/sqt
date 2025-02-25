#pragma once

#include <sqt/orm/querier/where_querier.h>

namespace sqt {

template<typename QUERIER>
class WhereCapacity {
public:
    template<ExpressionLike EXPRESSION>
    constexpr auto Where(EXPRESSION expression) const {

        return WhereQuerier<QUERIER, EXPRESSION>{
            static_cast<const QUERIER&>(*this),
            std::move(expression)
        };
    }
};

}