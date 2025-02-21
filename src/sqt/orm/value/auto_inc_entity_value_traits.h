#pragma once

#include <sqt/foundation/statement.h>
#include <sqt/orm/value/entire_entity_value_traits.h>
#include <sqt/orm/value/entity_value_type.h>

namespace sqt {

template<EntityValueType T>
class AutoIncEntityValueTraits {
public:
    using ValueType = T;
    using EntityType = T;
    using TableType = TableT<T>;

    static constexpr std::size_t ParameterCount = 
        TableType::GetColumns().size() - TableType::PrimaryKeyType::ColumnCount;

    static void BindValueToStatement(Statement& statement, int parameter_index, const T& value) {

        int index = parameter_index;
        for (auto each_column : TableType::GetNonPrimaryKeyColumns()) {
            each_column->BindValueToStatement(statement, index++, value);
        }
    }

    static T GetValueFromStatement(const Statement& statement, int column_index) {
        // Forwards to EntireEntityValueTraits.
        return EntireEntityValueTraits<T>::GetValueFromStatement(statement, column_index);
    }
};

}