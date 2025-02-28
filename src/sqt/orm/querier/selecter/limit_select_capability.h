#pragma once

#include <sqt/orm/expression/operand/placeholder.h>
#include <sqt/orm/expression/operand/placeholder_operand.h>
#include <sqt/orm/expression/operand/value_operand.h>
#include <sqt/orm/querier/selecter/limit_select_decorator.h>
#include <sqt/orm/value/trivial_value_traits.h>

namespace sqt {

template<typename SELECTER>
class LimitSelectCapability {
public:
    constexpr auto Limit(std::size_t limit) const {

        using ValueTraits = TrivialValueTraits<std::size_t>;
        using Operand = ValueOperand<ValueTraits>;

        return LimitSelectDecorator<SELECTER, Operand>{ 
            static_cast<const SELECTER&>(*this), 
            Operand{ limit }
        };
    }

    constexpr auto Limit(Placeholder) const {

        using ValueTraits = TrivialValueTraits<std::size_t>;
        using Operand = PlaceholderOperand<ValueTraits>;

        return LimitSelectDecorator<SELECTER, Operand> {
            static_cast<const SELECTER&>(*this),
            Operand{},
        };
    }
};

}