#pragma once

#include <sqt/orm/binder/value_binder.h>
#include <sqt/orm/expression/operand.h>
#include <sqt/orm/expression/placeholder.h>
#include <sqt/orm/utility/utility.h>
#include <sqt/orm/value_type/composite_value_type.h>
#include <sqt/orm/value_type/entity_value_type.h>

namespace sqt {

class ValueOperand {

};

template<typename T>
class Operand<T, std::enable_if_t<
    PrimitiveValueLike<T> || NullableValueLike<T> || CompositeValueLike<T> || EntityValueLike<T>>>
    :
    public ValueOperand {

public:
    using ValueType = T;

    static constexpr std::size_t ParameterCount = ValueTypeTraits<T>::ParameterCount;

    static std::string BuildSQL() {
        return std::format("{}", JoinPlaceholders(ParameterCount));
    }

    static constexpr std::tuple<> BuildPlaceholderBinders(int parameter_index) noexcept {
        return {};
    }

public:
    constexpr explicit Operand(T value) : value_(std::move(value)) {

    }

    void BindInlineParameters(Statement& statement, int parameter_index) const {
        ValueTypeTraits<T>::BindValueToStatement(statement, parameter_index, value_);
    }

private:
    T value_{};
};


template<typename T>
class Operand<T, std::enable_if_t<PlaceholderType<T>>> : public ValueOperand {
public:
    using ValueType = typename T::ValueType;

    static constexpr std::size_t ParameterCount = ValueTypeTraits<ValueType>::ParameterCount;

    static std::string BuildSQL() {
        return std::format("{}", JoinPlaceholders(ParameterCount));
    }

    static constexpr std::tuple<ValueBinder<ValueType>> BuildPlaceholderBinders(
        int parameter_index) noexcept {

        return std::make_tuple(ValueBinder<ValueType>{ parameter_index });
    }

public:
    constexpr Operand() noexcept = default;

    constexpr void BindInlineParameters(Statement& statement, int parameter_index) const noexcept {

    }
};

}