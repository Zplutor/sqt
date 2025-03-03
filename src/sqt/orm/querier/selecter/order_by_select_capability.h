#pragma once

#include <sqt/orm/querier/selecter/order_by_select_decorator.h>

namespace sqt {

template<typename SELECTER>
class OrderBySelectCapability {
public:
    template<OrderingTermType... TERM>
    constexpr auto OrderBy(TERM... terms) const {
        return OrderBySelectDecorator<SELECTER, TERM...>{
            static_cast<const SELECTER&>(*this)
        };
    }
};

}