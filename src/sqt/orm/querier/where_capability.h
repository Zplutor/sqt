#pragma once

#include <sqt/orm/querier/where_decorator.h>

namespace sqt {

template<typename QUERIER, template<typename, typename> typename DECORATOR = WhereDecorator>
class WhereCapability {
public:
    template<PredicateType PREDICATE>
    constexpr auto Where(PREDICATE predicate) const {

        return DECORATOR<QUERIER, PREDICATE>{
            static_cast<const QUERIER&>(*this),
            std::move(predicate)
        };
    }
};

}