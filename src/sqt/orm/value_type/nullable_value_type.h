#pragma once

#include <sqt/orm/value_type/primitive_value_type.h>

namespace sqt {

template<typename T>
struct IsOptional : std::false_type {};

template<typename E>
struct IsOptional<std::optional<E>> : std::true_type {};

template<typename T>
constexpr bool IsOptionalV = IsOptional<T>::value;


template<typename T>
struct GetOptionalValueType {
    using type = void;
};

template<typename E>
struct GetOptionalValueType<std::optional<E>> {
    using type = E;
};

template<typename T>
using GetOptionalValueTypeT = typename GetOptionalValueType<T>::type;


template<typename T>
constexpr bool IsNullableValueTypeV =
    IsOptionalV<T> &&
    IsPrimitiveValueTypeV<GetOptionalValueTypeT<T>>;


template<typename T>
struct ValueTypeTraits<T, std::enable_if_t<IsNullableValueTypeV<T>>> {

    static constexpr sqt::DataType DataType = MapToDataTypeV<GetOptionalValueTypeT<T>>;
    static constexpr bool IsNullable = true;

    static constexpr std::size_t PlaceholderCount = 1;

    static int BindValueToStatement(Statement& statement, int parameter_index, const T& value) {
        if (value.has_value()) {
            statement.BindParameter(parameter_index, *value);
        }
        return parameter_index + 1;
    }

    static T GetValueFromStatement(const Statement& statement, int column_index) {

        auto column_type = statement.GetColumnType(column_index);
        if (column_type == DataType::Null) {
            return std::nullopt;
        }

        return ValueTypeTraits<GetOptionalValueTypeT<T>>::GetValueFromStatement(
            statement,
            column_index);
    }
};

}