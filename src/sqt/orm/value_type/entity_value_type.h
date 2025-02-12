#pragma once

#include <sqt/foundation/statement.h>
#include <sqt/orm/value_type/value_type_traits.h>
#include <sqt/orm/table_mapping.h>

namespace sqt {

template<typename T>
concept EntityValueLike = requires {
    typename Table<T>::type;
};

template<EntityValueLike T>
struct ValueTypeTraits<T> {

    static constexpr std::size_t ParameterCount = TableV<T>.GetColumns().size();

    static void BindValueToStatement(Statement& statement, int parameter_index, const T& value) {

        int index = parameter_index;
        for (auto each_column : TableV<T>.GetColumns()) {
            each_column->BindValueToStatement(statement, index++, value);
        }
    }

    static T GetValueFromStatement(const Statement& statement, int column_index) {

        T result{};
        int index = column_index;
        for (auto each_column : TableV<T>.GetColumns()) {
            each_column->GetValueFromStatement(statement, index++, result);
        }
        return result;
    }
};

}