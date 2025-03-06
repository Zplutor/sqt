#pragma once

#include <sqt/orm/value/value_traits_type.h>
#include <sqt/orm/utility/utility.h>

namespace sqt {

template<ValueTraitsType TRAITS>
class ConstantOperand {
public:
    using ValueTraits = TRAITS;
    using ValueType = typename TRAITS::ValueType;

    static constexpr std::size_t ParameterCount = ValueTraits::ParameterCount;

    static std::string BuildSQL() {
        return std::format("{}", JoinPlaceholders(ParameterCount));
    }

    static constexpr std::tuple<> BuildPlaceholderBinders(int parameter_index) noexcept {
        return {};
    }

public:
    constexpr explicit ConstantOperand(ValueType value) : value_(std::move(value)) {

    }

    void BindInlineParameters(Statement& statement, int parameter_index) const {
        ValueTraits::BindValueToStatement(statement, parameter_index, value_);
    }

private:
    ValueType value_{};
};

}