#pragma once

#include <sqt/foundation/statement.h>
#include <sqt/orm/value_type/entire_entity_value_traits.h>
#include <sqt/orm/value_type/entity_value_like.h>

namespace sqt {

template<EntityValueLike T>
class AutoIncEntityValueTraits {
public:
    static constexpr std::size_t ParameterCount = 
        TableT<T>::GetColumns().size() - TableT<T>::PrimaryKeyType::ColumnCount;

    static void BindValueToStatement(Statement& statement, int parameter_index, const T& value) {

        int index = parameter_index;
        for (auto each_column : TableT<T>.GetColumns()) {
            each_column->BindValueToStatement(statement, index++, value);
        }
    }

    static T GetValueFromStatement(const Statement& statement, int column_index) {
        // Forwards to EntireEntityValueTraits.
        return EntireEntityValueTraits<T>::GetValueFromStatement(statement, column_index);
    }
};

}