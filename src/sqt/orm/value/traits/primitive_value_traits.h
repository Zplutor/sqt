#pragma once

#include <concepts>
#include <sqt/foundation/data_type.h>
#include <sqt/foundation/statement.h>

namespace sqt {

template<typename T>
class PrimitiveValueTraits;


template<std::integral T>
class PrimitiveValueTraits<T> {
public:
    using ValueType = T;

    static constexpr sqt::DataType DataType = sqt::DataType::Integer;
    static constexpr bool IsNullable = false;
    static constexpr std::size_t ParameterCount = 1;

    static void BindValue(Statement& statement, int parameter_index, const T& value) {
        statement.BindParameter(parameter_index, value);
    }

    static T RetrieveValue(const Statement& statement, int column_index) {
        if constexpr (sizeof(T) >= sizeof(std::int64_t)) {
            return static_cast<T>(statement.GetColumnInt64(column_index));
        }
        return static_cast<T>(statement.GetColumnInt(column_index));
    }
};


template<std::floating_point T>
class PrimitiveValueTraits<T> {
public:
    using ValueType = T;

    static constexpr sqt::DataType DataType = sqt::DataType::Float;
    static constexpr bool IsNullable = false;
    static constexpr std::size_t ParameterCount = 1;

    static void BindValue(Statement& statement, int parameter_index, const T& value) {
        statement.BindParameter(parameter_index, value);
    }

    static T RetrieveValue(const Statement& statement, int column_index) {
        return static_cast<T>(statement.GetColumnDouble(column_index));
    }
};


template<>
class PrimitiveValueTraits<std::string> {
public:
    using ValueType = std::string;

    static constexpr sqt::DataType DataType = sqt::DataType::Text;
    static constexpr bool IsNullable = false;
    static constexpr std::size_t ParameterCount = 1;

    static void BindValue(Statement& statement, int parameter_index, const std::string& value) {
        statement.BindParameter(parameter_index, value);
    }

    static std::string RetrieveValue(const Statement& statement, int column_index) {
        return std::string{ statement.GetColumnText(column_index) };
    }
};

}