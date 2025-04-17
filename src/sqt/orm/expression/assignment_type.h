#pragma once

/**
@file
    Defines the `sqt::AssignmentType` concept.
*/

#include <sqt/orm/expression/assignment_operator.h>
#include <sqt/orm/expression/expression_like.h>

namespace sqt {

/**
Constraints a type to be an assignment type, which associates an identifier with a value.

@details 
    @b Requirements
    - The type must satisfy the `sqt::ExpressionLike` concept.
    - The type must have a static constant `Operator` of type `sqt::AssignmentOperator`.

    Assignments are used in inserters and updaters to assign values to identifiers like columns, 
    primary keys and indexes.

    To create an assignment, use the assignment operator `=` on the identifier to assign a value or
    a placeholder. Consider the following entity type and its table definition:

    @code{.cpp}
    struct MyEntity {
        int id{};
        std::string name;
    };
    SQT_TABLE_BEGIN(MyEntity, MyEntity)
    SQT_COLUMN_FIELD(id, id)
    SQT_COLUMN_FIELD(name, name)
    SQT_PRIMARY_KEY(id)
    SQT_INDEX(id, name)
    SQT_TABLE_END
    @endcode

    Example of creating an inserter with assignments:
    @code{.cpp}
    // Inserter with assignments of columns, using inline values.
    auto inserter = sqt::DataContext<MyEntity>::MakeInserter(
        sqt::Table<MyEntity>.id = 1, 
        sqt::Table<MyEntity>.name = "The Name"
    );

    // Inserter with assignments of primary key and column, using placeholders.
    auto inserter = sqt::DataContext<MyEntity>::MakeInserter(
        sqt::Table<MyEntity>.PrimaryKey = sqt::_,
        sqt::Table<MyEntity>.name = sqt::_
    );

    //Inserter with assignment of an index, which uses a composite value.
    auto inserter = sqt::DataContext<MyEntity>::MakeInserter(
        sqt::Table<MyEntity>::Index_idname = std::make_tuple(1, "The Name")
    );
    @endcode

@see sqt::AssignmentOperator
@see sqt::ExpressionLike
*/
template<typename T>
concept AssignmentType = ExpressionLike<T> && requires {
    { T::Operator } -> std::same_as<const AssignmentOperator&>;
};

}