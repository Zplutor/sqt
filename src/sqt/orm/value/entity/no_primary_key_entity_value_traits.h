#pragma once

#include <sqt/foundation/statement.h>
#include <sqt/orm/value/entity/entity_value_type.h>

namespace sqt {

template<PrimaryKeyEntityValueType T>
class NoPrimaryKeyEntityValueTraits {
public:
    using ValueType = T;
    using EntityType = T;
    using TableType = TableT<T>;

    static constexpr ColumnsView<EntityType> ManipulatingColumns =
        TableType::GetNonPrimaryKeyColumns();

    static void BindValue(Statement& statement, int parameter_index, const T& value) {

        int index = parameter_index;
        for (auto each_column : ManipulatingColumns) {
            each_column->BindValueFromEntity(statement, index++, value);
        }
    }

    static T RetrieveValue(const Statement& statement, int column_index) {

        T entity;
        int index = column_index;
        for (auto each_column : ManipulatingColumns) {
            each_column->RetrieveValueToEntity(statement, index++, entity);
        }
        return entity;
    }
};

}