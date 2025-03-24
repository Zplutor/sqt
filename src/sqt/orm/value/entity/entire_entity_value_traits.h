#pragma once

#include <sqt/foundation/statement.h>
#include <sqt/orm/table/column/column.h>
#include <sqt/orm/value/entity/entity_value_type.h>

namespace sqt {

template<EntityValueType T>
class EntireEntityValueTraits {
public:
    using ValueType = T;
    using EntityType = T;
    using TableType = TableType<T>;

    static constexpr ColumnsView<EntityType> ManipulatingColumns = TableType::GetColumns();

    static void BindValue(Statement& statement, int parameter_index, const T& value) {

        int index = parameter_index;
        for (auto each_column : ManipulatingColumns) {
            each_column->BindValueFromEntity(statement, index++, value);
        }
    }

    static T RetrieveValue(const Statement& statement, int column_index) {

        T result{};
        int index = column_index;
        for (auto each_column : ManipulatingColumns) {
            each_column->RetrieveValueToEntity(statement, index++, result);
        }
        return result;
    }
};

}