#pragma once

#include <sqt/orm/expression/binder/binder.h>
#include <sqt/orm/internal/parameter_count_deduction.h>
#include <sqt/orm/internal/utility.h>
#include <sqt/orm/value/value_traits_type.h>

namespace sqt {

template<ValueTraitsType TRAITS>
class PlaceholderOperand {
public:
    using ValueTraits = TRAITS;
    using ValueType = typename TRAITS::ValueType;

    static constexpr std::size_t ParameterCount = internal::ParameterCountForV<TRAITS>;

    static std::string BuildSQL() {
        return std::format("{}", internal::JoinPlaceholders(ParameterCount));
    }

    static constexpr auto BuildPlaceholderBinders(int parameter_index) noexcept {
        return std::make_tuple(Binder<ValueTraits>{ parameter_index });
    }

public:
    constexpr PlaceholderOperand() noexcept = default;

    constexpr void BindInlineParameters(Statement& statement, int parameter_index) const noexcept {

    }
};

}