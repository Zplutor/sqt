#pragma once

/**
@file
    Defines the `sqt::AbstractPrimaryKey` interface.
*/

#include <sqt/orm/table/column/abstract_column.h>

namespace sqt {

/**
An interface that provides access to information about the primary key of a table.

@details
    This interface is implemented by all primary key types defined using the `SQT_PRIMARY_KEY` or 
    `SQT_PRIMARY_KEY_AUTO_INC` macros. It allows the way to interact with primary key definitions 
    in a non-template manner.

@see SQT_PRIMARY_KEY
@see SQT_PRIMARY_KEY_AUTO_INC
@see sqt::AbstractTable
*/
class AbstractPrimaryKey {
public:
    constexpr AbstractPrimaryKey() = default;

    AbstractPrimaryKey(const AbstractPrimaryKey&) = delete;
    AbstractPrimaryKey& operator=(const AbstractPrimaryKey&) = delete;

    /**
    Gets all columns that form the primary key.

    @return
        A view to columns that form the primary key.
    */
    virtual AbstractColumnsView GetAbstractColumns() const noexcept = 0;

    /**
    Checks whether the primary key is auto-incremented.

    @return
        `true` if the primary key is auto-incremented; otherwise `false`.
    */
    virtual bool IsAutoInc() const noexcept = 0;
};

}