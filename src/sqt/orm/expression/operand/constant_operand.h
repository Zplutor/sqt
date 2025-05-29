#pragma once

#include <sqt/orm/internal/parameter_count_deduction.h>
#include <sqt/orm/internal/utility.h>
#include <sqt/orm/value/value_traits_type.h>

namespace sqt {

template<ValueTraitsType TRAITS>
class ConstantOperand {
public:
    using ValueTraits = TRAITS;
    using ValueType = typename TRAITS::ValueType;

    static constexpr std::size_t ParameterCount = internal::ParameterCountForV<TRAITS>;

    static std::string BuildSQL() {
        return std::format("{}", internal::JoinPlaceholders(ParameterCount));
    }

    static constexpr std::tuple<> BuildPlaceholderBinders(int parameter_index) noexcept {
        return {};
    }

public:
    constexpr explicit ConstantOperand(ValueType value) : value_(std::move(value)) {

    }

    void BindInlineParameters(Statement& statement, int parameter_index) const {
        ValueTraits::BindValue(statement, parameter_index, value_);
    }

private:
    ValueType value_{};
};

}