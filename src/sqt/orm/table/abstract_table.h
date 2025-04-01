#pragma once

/**
@file
    Defines the `sqt::AbstractTable` class.
*/

#include <string_view>
#include <sqt/orm/table/column/abstract_column.h>
#include <sqt/orm/table/index/abstract_index.h>
#include <sqt/orm/table/primary_key/abstract_primary_key.h>

namespace sqt {

/**
An interface to access information of a table.

@details
    This interface is provided to write non-template code that works with tables. Every table type 
    defined by the `SQT_TABLE_BEGIN` macro implements this interface.

@see SQT_TABLE_BEGIN
*/
class AbstractTable {
public:
    constexpr AbstractTable() = default;

    AbstractTable(const AbstractTable&) = delete;
    AbstractTable& operator=(const AbstractTable&) = delete;

    /**
    Gets the name of the table.

    @return
        The name fo the table.
    */
    virtual std::string_view GetName() const noexcept = 0;

    /**
    Gets all columns of the table.

    @return
        A view to all columns of the table. It is empty if the table does not have columns.
    */
    virtual AbstractColumnsView GetAbstractColumns() const noexcept = 0;

    /**
    Gets all indexes of the table.

    @return
        A view to all indexes of the table. It is empty if the table does not have any indexes.
    */
    virtual AbstractIndexesView GetAbstractIndexes() const noexcept = 0;

    /**
    Gets the primary key of the table.

    @return
        A pointer to the primary key; or `nullptr` if the table does not have a primary key.
    */
    virtual constexpr const AbstractPrimaryKey* GetAbstractPrimaryKey() const noexcept {
        return nullptr;
    }
};

}