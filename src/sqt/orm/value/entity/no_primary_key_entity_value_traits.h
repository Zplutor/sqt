#pragma once

/**
@file
    Defines the `sqt::NoPrimaryKeyEntityValueTraits` class template.
*/

#include <sqt/foundation/statement.h>
#include <sqt/orm/internal/column_helper.h>
#include <sqt/orm/value/entity/entity_value_type.h>

namespace sqt {

/**
Defines traits for manipulating the non-primary key columns of an entity value type.

@tparam T
    A type that satisfies the `sqt::PrimaryKeyEntityValueType` concept.

@details
    This class template satisfies the `sqt::EntityValueTraitsType` concept.

@see sqt::EntityValueTraitsType
@see sqt::PrimaryKeyEntityValueType
*/
template<PrimaryKeyEntityValueType T>
class NoPrimaryKeyEntityValueTraits {
public:
    using ValueType = T;
    using EntityType = T;
    using TableType = TableType<T>;

    static constexpr ColumnsView<EntityType> ManipulatingColumns =
        TableType::GetInstance().GetNonPrimaryKeyColumns();

    /**
    Binds the non-primary key columns of the entity value to the statement, starting at the
    specified parameter index.

    @param statement
        The statement to which the value is bound.

    @param parameter_index
        The starting index of the parameters to which the value is bound.

    @param value
        The entity value to bind.

    @throw sqt::SQLError
        Thrown if the binding fails.

    @details
        This method delegates to the `BindValueFromEntity()` method of each non-primary key column 
        in the entity's table type. The parameter index is incremented for each column.

    @see sqt::Column<>::BindValueFromEntity()
    */
    static void BindValue(Statement& statement, int parameter_index, const EntityType& value) {
        internal::BindColumnValuesFromEntity(
            statement,
            parameter_index,
            value,
            ManipulatingColumns);
    }

    /**
    Retrieves the non-primary key columns of the entity value from the statement, starting at the 
    specified column index.

    @param statement
        The statement from which the value is retrieved.

    @param column_index
        The starting index of the columns from which the value is retrieved.

    @return
        The retrieved entity value. Its values corresponding to the non-primary key columns are 
        left intact.

    @details
        This method delegates to the `RetrieveValueToEntity()` method of each non-primary key 
        column in the entity's table type. The column index is incremented for each column.

    @see sqt::Column<>::RetrieveValueToEntity()
    */
    static EntityType RetrieveValue(const Statement& statement, int column_index) {
        return internal::RetrieveColumnValuesToEntity(
            statement,
            column_index,
            ManipulatingColumns);
    }
};

}