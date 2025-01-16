#pragma once

#include <sqt/orm/querier/selecter/limit_selecter.h>

namespace sqt {

template<typename SELECTER>
class LimitCapacity {
public:
    constexpr auto Limit(std::size_t limit) const {
        return LimitSelecter<SELECTER, Operand<std::size_t>>{
            static_cast<const SELECTER&>(*this),
                Operand<std::size_t>{ limit }
        };
    }

    constexpr auto Limit(PlaceholderTag) const {
        return LimitSelecter<SELECTER, Operand<Placeholder<std::size_t>>> {
            static_cast<const SELECTER&>(*this),
                Operand<Placeholder<std::size_t>>{},
        };
    }
};

}