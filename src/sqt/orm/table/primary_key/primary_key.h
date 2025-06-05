#pragma once

/**
@file
    Defines the `sqt::PrimaryKey<>` class template.
*/

#include <sqt/orm/table/primary_key/abstract_primary_key.h>
#include <sqt/orm/table/column/composite_column.h>

namespace sqt {

/**
Represents a primary key for a table, which is a composite of one or more columns.

@tparam COLUMNS
    The column types that make up the primary key. Each column must satisfy the `sqt::ColumnType` 
    concept and must not be nullable.

@details
    This class template is a base class for all primary key types defined using the 
    `SQT_PRIMARY_KEY` or `SQT_PRIMARY_KEY_AUTO_INC` macros.

@see sqt::ColumnType
@see SQT_PRIMARY_KEY
@see SQT_PRIMARY_KEY_AUTO_INC
*/
template<ColumnType... COLUMNS>
class PrimaryKey : public CompositeColumn<COLUMNS...>, public AbstractPrimaryKey {
    static_assert(
        !(COLUMNS::ValueTraits::IsNullable && ...),
        "Primary key columns cannot be nullable.");

public:
    constexpr PrimaryKey() noexcept = default;

    AbstractColumnsView GetAbstractColumns() const noexcept override {
        return CompositeColumn<COLUMNS...>::GetAbstractColumns();
    }
};


/**
A helper function to deduce the type of a primary key from columns.

@tparam COLUMNS
    The column types that make up the primary key.

@param columns
    The column instances. They are only used to deduce the column types and will not be used.

@return
    The `sqt::PrimaryKey<>` type deduced from the provided columns.

@relates sqt::PrimaryKey
*/
template<ColumnType... COLUMNS>
PrimaryKey<COLUMNS...> MakePrimaryKey(const COLUMNS&... columns) {}

}