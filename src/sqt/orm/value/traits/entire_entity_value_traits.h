#pragma once

#include <sqt/foundation/statement.h>
#include <sqt/orm/table/column.h>
#include <sqt/orm/value/entity_value_type.h>

namespace sqt {

template<EntityValueType T>
class EntireEntityValueTraits {
public:
    using ValueType = T;
    using EntityType = T;
    using TableType = TableT<T>;

    static constexpr ColumnsView<EntityType> InsertingColumns = TableType::GetColumns();
    static constexpr ColumnsView<EntityType> SelectingColumns = TableType::GetColumns();

    static constexpr std::size_t ParameterCount = InsertingColumns.size();

    static void BindValue(Statement& statement, int parameter_index, const T& value) {

        int index = parameter_index;
        for (auto each_column : InsertingColumns) {
            each_column->VirtualBindValueFromEntity(statement, index++, value);
        }
    }

    static T RetrieveValue(const Statement& statement, int column_index) {

        T result{};
        int index = column_index;
        for (auto each_column : SelectingColumns) {
            each_column->VirtualRetrieveValueToEntity(statement, index++, result);
        }
        return result;
    }
};

}