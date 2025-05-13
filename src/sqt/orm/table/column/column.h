#pragma once

/**
@file
    Defines the `sqt::Column<>` class template and the `sqt::ColumnsView<>` type alias.
*/

#include <span>
#include <sqt/foundation/statement.h>
#include <sqt/orm/table/column/abstract_column.h>

namespace sqt {

/**
Represents a column in a table that is associated with a specific entity type.

@tparam ENTITY
    The type of the entity that the column is associated with.

@details
    This interface extends the `sqt::AbstractColumn` interface by associating the column with a 
    specific entity type. It can be used as the element type for a collection of columns that are 
    associated with the same entity type.

    This interface is implemented by all column types defined using the `SQT_COLUMN_FIELD`,
    `SQT_COLUMN_ACCESSOR` and `SQT_COLUMN_CUSTOM` macros.

@see sqt::AbstractColumn
@see SQT_COLUMN_ACCESSOR
@see SQT_COLUMN_CUSTOM
@see SQT_COLUMN_FIELD
*/
template<typename ENTITY>
class Column : public AbstractColumn {
public:
    /**
    The entity type that the column is associated with.
    */
    using EntityType = ENTITY;

public:
    constexpr Column() noexcept = default;

    /**
    Binds the column value extracted from an entity to the statement at the specified parameter 
    index.

    @param statement
        The statement to which the value is bound.

    @param parameter_index
        The index of the parameter to which the value is bound.

    @param entity
        The entity from which the value is extracted.

    @throw sqt::SQLError
        Thrown if the binding fails.
    */
    virtual void BindValueFromEntity(
        Statement& statement,
        int parameter_index,
        const ENTITY& entity) const = 0;

    /**
    Retrieves the column value from the statement and sets it to the entity.

    @param statement
        The statement from which the value is retrieved.

    @param column_index
        The index of the column from which the value is retrieved.

    @param entity
        The entity to which the value is set.
    */
    virtual void RetrieveValueToEntity(
        const Statement& statement,
        int index,
        ENTITY& entity) const = 0;
};


/**
A view to a collection of `sqt::Column<>` for a specific entity type.
*/
template<typename ENTITY>
using ColumnsView = std::span<const Column<ENTITY>* const>;

}