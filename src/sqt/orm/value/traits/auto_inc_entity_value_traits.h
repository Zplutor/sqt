#pragma once

#include <sqt/foundation/statement.h>
#include <sqt/orm/value/traits/entire_entity_value_traits.h>
#include <sqt/orm/value/entity_value_type.h>

namespace sqt {

template<AutoIncEntityValueType T>
class AutoIncEntityValueTraits {
public:
    using ValueType = T;
    using EntityType = T;
    using TableType = TableT<T>;

    static constexpr ColumnsView<EntityType> InsertingColumns = 
        TableType::GetNonPrimaryKeyColumns();

    static constexpr std::size_t ParameterCount = InsertingColumns.size();

    static void BindValue(Statement& statement, int parameter_index, const T& value) {

        int index = parameter_index;
        for (auto each_column : InsertingColumns) {
            each_column->VirtualBindValueFromEntity(statement, index++, value);
        }
    }

    static T RetrieveValue(const Statement& statement, int column_index) {
        // Forwards to EntireEntityValueTraits.
        return EntireEntityValueTraits<T>::RetrieveValue(statement, column_index);
    }
};

}