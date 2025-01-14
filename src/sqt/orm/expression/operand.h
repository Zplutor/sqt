#pragma once

#include <sqt/orm/binder/value_binder.h>
#include <sqt/orm/column.h>
#include <sqt/orm/expression/placeholder.h>
#include <sqt/orm/utility/utility.h>
#include <sqt/orm/value_type/composite_value_type.h>

namespace sqt {

template<typename T, typename = void>
class Operand;


//Used for individual column.
template<typename T>
class Operand<T, std::enable_if_t<IsColumnV<T>>> {
public:
    static constexpr std::size_t ParameterCount = 0;

    static constexpr std::tuple<> BuildPlaceholderBinder(int parameter_index) noexcept {
        return {};
    }

public:
    explicit Operand(const T& column) : column_(&column) {

    }

    std::string BuildSQL() const {
        return std::string{ column_->GetName() };
    }

    constexpr void BindInlineParameters(Statement& statement, int parameter_index) const noexcept {

    }

private:
    const T* column_{};
};


/*
//Used for composite columns such as primary key and index.
template<typename T>
class Operand<T, std::enable_if_t<IsCompositeColumnBasedV<T>>> {
public:
    explicit Operand(const T& composite_column) : composite_column_(&composite_column) {

    }

    std::string BuildSQL() const {
        return std::format("({})", JoinColumnNames(composite_column_->GetAbstractColumns()));
    }

    int BindParameters(Statement& statement, int begin_index) const {
        return begin_index;
    }

private:
    const T* composite_column_{};
};
*/


template<typename T>
class Operand<T, std::enable_if_t<
    IsPrimitiveValueTypeV<T> || IsNullableValueTypeV<T> || IsCompositeValueTypeV<T>>> {

public:
    using ValueType = T;

    static constexpr std::size_t ParameterCount = ValueTypeTraits<T>::PlaceholderCount;

    static constexpr std::tuple<> BuildPlaceholderBinder(int parameter_index) noexcept {
        return {};
    }

public:
    constexpr explicit Operand(T value) : value_(std::move(value)) {

    }

    std::string BuildSQL() const {
        if constexpr (ParameterCount == 1) {
            return "?";
        }
        return std::format("({})", JoinPlaceholders(ParameterCount));
    }

    void BindInlineParameters(Statement& statement, int parameter_index) const {
        ValueTypeTraits<T>::BindValueToStatement(statement, parameter_index, value_);
    }

private:
    T value_{};
};


template<typename T>
class Operand<T, std::enable_if_t<PlaceholderType<T>>> {
public:
    using ValueType = typename T::ValueType;

    static constexpr std::size_t ParameterCount = ValueTypeTraits<ValueType>::PlaceholderCount;

    static constexpr std::tuple<ValueBinder<ValueType>> BuildPlaceholderBinder(
        int parameter_index) noexcept {

        return std::make_tuple(ValueBinder<ValueType>{ parameter_index });
    }

public:
    constexpr Operand() noexcept = default;

    std::string BuildSQL() const {
        return "?";
    }

    constexpr void BindInlineParameters(Statement& statement, int parameter_index) const noexcept {

    }
};

}
