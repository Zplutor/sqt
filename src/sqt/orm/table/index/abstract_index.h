#pragma once

/**
@file
    Defines the `sqt::AbstractIndex` interface and the `sqt::AbstractIndexesView` type alias.
*/

#include <span>
#include <sqt/orm/table/column/abstract_column.h>

namespace sqt {

/**
An interface that provides access to information about an index.

@details
    This interface is implemented by all index types defined using the `SQT_INDEX`, `SQT_INDEX_2`,
    `SQT_INDEX_UNIQUE` and `SQT_INDEX_UNIQUE_2` macros. It allows the way to interact with index 
    definitions in a non-template manner.

@see SQT_INDEX
@see SQT_INDEX_2
@see SQT_INDEX_UNIQUE
@see SQT_INDEX_UNIQUE_2
*/
class AbstractIndex {
public:
    constexpr AbstractIndex() noexcept = default;

    AbstractIndex(const AbstractIndex&) = delete;
    AbstractIndex& operator=(const AbstractIndex&) = delete;

    /**
    Gets the name of the index.

    @return
        The name of the index.
    */
    virtual std::string_view GetName() const noexcept = 0;

    /**
    Gets columns of the index.

    @return
        A view to the columns of the index.

    @see sqt::AbstractColumn
    */
    virtual AbstractColumnsView GetAbstractColumns() const noexcept = 0;

    /**
    Indicates whether the index is unique.

    @return
        `true` if the index is unique; otherwise `false`.
    */
    virtual bool IsUnique() const noexcept = 0;
};

/**
A view to a collection of `sqt::AbstractIndex`.
*/
using AbstractIndexesView = std::span<const AbstractIndex* const>;

}