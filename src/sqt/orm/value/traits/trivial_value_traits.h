#pragma once

#include <sqt/foundation/statement.h>
#include <sqt/orm/value/composite_value_type.h>
#include <sqt/orm/value/data_type_mapping.h>
#include <sqt/orm/value/nullable_value_type.h>
#include <sqt/orm/value/primitive_value_type.h>

namespace sqt {

template<typename T>
struct TrivialValueTraits;


template<PrimitiveValueType T>
struct TrivialValueTraits<T> {

    using ValueType = T;

    static constexpr sqt::DataType DataType = MapToDataTypeV<T>;
    static constexpr bool IsNullable = false;

    static constexpr std::size_t ParameterCount = 1;

    static void BindValueToStatement(Statement& statement, int parameter_index, const T& value) {
        statement.BindParameter(parameter_index, value);
    }

    static T GetValueFromStatement(const Statement& statement, int column_index) {

        if constexpr (std::is_integral_v<T>) {
            if constexpr (sizeof(T) >= sizeof(std::int64_t)) {
                return static_cast<T>(statement.GetColumnInt64(column_index));
            }
            return static_cast<T>(statement.GetColumnInt(column_index));
        }

        if constexpr (std::is_floating_point_v<T>) {
            return static_cast<T>(statement.GetColumnDouble(column_index));
        }

        if constexpr (std::is_same_v<std::string, T>) {
            return std::string{ statement.GetColumnText(column_index) };
        }
    }
};


template<NullableValueType T>
struct TrivialValueTraits<T> {

    using ValueType = T;

    static constexpr sqt::DataType DataType = MapToDataTypeV<GetOptionalValueTypeT<T>>;
    static constexpr bool IsNullable = true;

    static constexpr std::size_t ParameterCount = 1;

    static void BindValueToStatement(Statement& statement, int parameter_index, const T& value) {
        if (value.has_value()) {
            statement.BindParameter(parameter_index, *value);
        }
    }

    static T GetValueFromStatement(const Statement& statement, int column_index) {

        auto column_type = statement.GetColumnType(column_index);
        if (column_type == DataType::Null) {
            return std::nullopt;
        }

        return TrivialValueTraits<GetOptionalValueTypeT<T>>::GetValueFromStatement(
            statement,
            column_index);
    }
};


template<CompositeValueType T>
struct TrivialValueTraits<T> {

    using ValueType = T;

    static constexpr std::size_t ParameterCount = std::tuple_size<T>::value;

    static void BindValueToStatement(Statement& statement, int parameter_index, const T& value) {

        int index = parameter_index;
        auto binder = [&statement, &index](const auto& value) {
            TrivialValueTraits<std::decay_t<decltype(value)>>::BindValueToStatement(
                statement,
                index,
                value);
            ++index;
        };

        std::apply(
            [&binder](const auto&... values) {
                (binder(values), ...);
            },
            value);
    }

    static T GetValueFromStatement(const Statement& statement, int column_index) {

        int index = column_index;
        auto getter = [&statement, &index](auto& value) {
            value = TrivialValueTraits<std::decay_t<decltype(value)>>::GetValueFromStatement(
                statement,
                index);
            ++index;
        };

        T result{};
        std::apply(
            [&getter](auto&... values) {
                (getter(values), ...);
            },
            result);

        return result;
    }
};

}