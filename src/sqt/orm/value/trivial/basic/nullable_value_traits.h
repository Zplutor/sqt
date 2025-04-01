#pragma once

#include <sqt/orm/value/trivial/basic/nullable_value_type.h>
#include <sqt/orm/value/trivial/basic/primitive_value_traits.h>

namespace sqt {

template<NullableValueType T>
class NullableValueTraits {
public:
    using ValueType = T;
    using InnerValueTriats = PrimitiveValueTraits<GetOptionalValueTypeT<T>>;

    static constexpr DataType DataType = InnerValueTriats::DataType;
    static constexpr bool IsNullable = true;

    static void BindValue(Statement& statement, int parameter_index, const T& value) {
        if (value.has_value()) {
            InnerValueTriats::BindValue(statement, parameter_index, *value);
        }
        else {
            statement.BindParameter(parameter_index, std::nullopt);
        }
    }

    static T RetrieveValue(const Statement& statement, int column_index) {

        auto column_type = statement.GetColumnType(column_index);
        if (column_type == DataType::Null) {
            return std::nullopt;
        }

        return InnerValueTriats::RetrieveValue(statement, column_index);
    }
};

}