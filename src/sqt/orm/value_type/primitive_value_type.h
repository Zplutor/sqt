#pragma once

#include <sqt/foundation/statement.h>
#include <sqt/orm/value_type/data_type_mapping.h>
#include <sqt/orm/value_type/value_type_traits.h>

namespace sqt {

template<typename T>
concept PrimitiveValueLike = requires {
    { MapToDataType<T>::value } -> std::same_as<const DataType&>;
};


template<PrimitiveValueLike T>
struct ValueTypeTraits<T> {

    static constexpr sqt::DataType DataType = MapToDataTypeV<T>;
    static constexpr bool IsNullable = false;

    static constexpr std::size_t ParameterCount = 1;

    static int BindValueToStatement(Statement& statement, int parameter_index, const T& value) {
        statement.BindParameter(parameter_index, value);
        return parameter_index + 1;
    }

    static T GetValueFromStatement(const Statement& statement, int column_index) {

        if constexpr (std::is_integral_v<T>) {
            if constexpr (sizeof(T) >= sizeof(std::int64_t)) {
                return static_cast<T>(statement.GetColumnInt64(column_index));
            }
            return static_cast<T>(statement.GetColumnInt(column_index));
        }

        if constexpr (std::is_same_v<std::string, T>) {
            return std::string{ statement.GetColumnText(column_index) };
        }
    }
};

}