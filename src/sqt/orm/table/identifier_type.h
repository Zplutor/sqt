#pragma once

/**
@file
    Defines the `sqt::IdentifierType` concept.
*/

#include <sqt/orm/table/column/column_type.h>
#include <sqt/orm/table/column/composite_column_type.h>

namespace sqt {

/**
Constrains a type to be an identifier type, which is a column type, primary key type or index type.

@details
    @b Requirements
    - The type must satisfies the `sqt::ColumnType` or `sqt::CompositeColumnType` concept.

    Identifiers can be used for expressions that require an identifier, such as assignment 
    expressions.

@see sqt::AssignmentType
@see sqt::ColumnType
@see sqt::CompositeColumnType
*/
template<typename T>
concept IdentifierType = ColumnType<T> || CompositeColumnType<T>;

}