#pragma once

#include <sqt/foundation/statement.h>
#include <sqt/orm/internal/column_helper.h>
#include <sqt/orm/value/entity/entity_value_type.h>

namespace sqt {

template<PrimaryKeyEntityValueType T>
class NoPrimaryKeyEntityValueTraits {
public:
    using ValueType = T;
    using EntityType = T;
    using TableType = TableType<T>;

    static constexpr ColumnsView<EntityType> ManipulatingColumns =
        TableType::GetInstance().GetNonPrimaryKeyColumns();

    static void BindValue(Statement& statement, int parameter_index, const T& value) {
        internal::BindColumnValuesFromEntity(
            statement,
            parameter_index,
            value,
            ManipulatingColumns);
    }

    static T RetrieveValue(const Statement& statement, int column_index) {
        return internal::RetrieveColumnValuesToEntity(
            statement,
            column_index,
            ManipulatingColumns);
    }
};

}