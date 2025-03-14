#pragma once

#include <sqt/foundation/statement.h>
#include <sqt/orm/value/primitive_value_type.h>

namespace sqt {

template<PrimitiveValueType T>
class PrimitiveValueTraits {
public:
    using ValueType = T;

    static constexpr std::size_t ParameterCount = 1;

    static void BindValue(Statement& statement, int parameter_index, const T& value) {
        statement.BindParameter(parameter_index, value);
    }

    static T RetrieveValue(const Statement& statement, int column_index) {

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

}