#pragma once

#include <sqt/orm/expression/binder/value_binder.h>
#include <sqt/orm/utility/utility.h>
#include <sqt/orm/value/value_traits_type.h>

namespace sqt {

template<ValueTraitsType TRAITS>
class PlaceholderOperand {
public:
    using ValueTraits = TRAITS;
    using ValueType = typename TRAITS::ValueType;

    static constexpr std::size_t ParameterCount = ValueTraits::ParameterCount;

    static std::string BuildSQL() {
        return std::format("{}", JoinPlaceholders(ParameterCount));
    }

    static constexpr auto BuildPlaceholderBinders(int parameter_index) noexcept {
        return std::make_tuple(ValueBinder<ValueTraits>{ parameter_index });
    }

public:
    constexpr PlaceholderOperand() noexcept = default;

    constexpr void BindInlineParameters(Statement& statement, int parameter_index) const noexcept {

    }
};

}