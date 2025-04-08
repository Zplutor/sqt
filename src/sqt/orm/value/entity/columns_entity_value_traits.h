#pragma once

#include <sqt/orm/internal/column_helper.h>
#include <sqt/orm/table/column/column.h>
#include <sqt/orm/table/column/column_type.h>
#include <sqt/orm/table_mapping.h>

namespace sqt {

template<ColumnType... COLUMNS>
class ColumnsEntityValueTraits {
private:
    static_assert(sizeof...(COLUMNS) > 0, "At least one column is required.");
    using FirstColumn = std::tuple_element_t<0, std::tuple<COLUMNS...>>;

    static_assert(
        (std::is_same_v<typename FirstColumn::EntityType, typename COLUMNS::EntityType> && ...),
        "All columns must have the same entity type.");

    using ColumnArrayType = std::array<
        const Column<typename FirstColumn::EntityType>*,
        sizeof...(COLUMNS)
    >;

    static constexpr ColumnArrayType ColumnArray = {
        Table<FirstColumn::EntityType>.template GetColumn<COLUMNS>()...
    };

public:
    using ValueType = typename FirstColumn::EntityType;
    using EntityType = typename FirstColumn::EntityType;
    using TableType = TableType<EntityType>;

    static constexpr ColumnsView<EntityType> ManipulatingColumns = ColumnArray;

    static void BindValue(Statement& statement, int parameter_index, const EntityType& value) {
        internal::BindColumnValuesFromEntity(
            statement,
            parameter_index,
            value,
            ManipulatingColumns);
    }

    static EntityType RetrieveValue(const Statement& statement, int column_index) {
        return internal::RetrieveColumnValuesToEntity(
            statement, 
            column_index, 
            ManipulatingColumns);
    }
};

}