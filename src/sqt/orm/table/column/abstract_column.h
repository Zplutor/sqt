#pragma once

/**
@file
    Defines the `sqt::AbstractColumn` interface and the `sqt::AbstractColumnsView` type alias.
*/

#include <span>
#include <sqt/foundation/data_type.h>

namespace sqt {

/**
An interface that provides access to information about a column of a table.

@details
    This interface is implemented by all column types defined using the `SQT_COLUMN_FIELD`,
    `SQT_COLUMN_ACCESSOR` and `SQT_COLUMN_CUSTOM` macros. It allows the way to interact with column 
    definitions in a non-template manner.

@see SQT_COLUMN_FIELD
@see SQT_COLUMN_ACCESSOR
@see SQT_COLUMN_CUSTOM
@see sqt::AbstractTable
*/
class AbstractColumn {
public:
    constexpr AbstractColumn() = default;

    AbstractColumn(const AbstractColumn&) = delete;
    AbstractColumn& operator=(const AbstractColumn&) = delete;

    /**
    Gets the name of the column.

    @return
        The name of the column.
    */
    virtual std::string_view GetName() const noexcept = 0;

    /**
    Gets the data type of the column.

    @return
        The data type of the column.
    */
    virtual DataType GetDataType() const noexcept = 0;

    /**
    Indicates whether the value of the column is nullable.

    @return
        `true` if the column is nullable; otherwise `false`.
    */
    virtual bool IsNullable() const noexcept = 0;
};


/**
A view to a collection of `sqt::AbstractColumn`.
*/
using AbstractColumnsView = std::span<const AbstractColumn* const>;

}
