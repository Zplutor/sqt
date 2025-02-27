#pragma once

#include <sqt/orm/querier/where_decorator.h>

namespace sqt {

template<typename QUERIER, template<typename, typename> typename DECORATOR = WhereDecorator>
class WhereCapability {
public:
    template<ExpressionLike EXPRESSION>
    constexpr auto Where(EXPRESSION expression) const {

        return DECORATOR<QUERIER, EXPRESSION>{
            static_cast<const QUERIER&>(*this),
            std::move(expression)
        };
    }
};

}