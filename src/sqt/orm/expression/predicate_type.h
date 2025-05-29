#pragma once

/**
@file
    Defines the `sqt::PredicateType` concept.
*/

#include <sqt/orm/expression/expression_like.h>
#include <sqt/orm/expression/predicate_operator.h>

namespace sqt {

/**
Constrains a type to be a predicate type.

@details
    @b Requirements
    - The type must satisfy the `sqt::ExpressionLike` concept.
    - The type must have a static constant `Operator` of type `sqt::PredicateOperator`, 
      representing the operator used in the predicate.

    Predicates are binary expressions that return a boolean, including comparison expressions
    and logical expressions. They are used in `WHERE` decorators of queriers to apply conditions to 
    the SQL statement.

    A predicate consists of an operator (specified by the `sqt::PredicateOperator` enum) and two
    operands (which must satisfy the `sqt::PredicateTermType` concept).

    To create predicates, use the comparison operators (`==`, `!=`, `<`, `<=`, `>`, `>=`) on 
    identifiers (including columns, primary keys and indexes), or logical operators (`&&`, `||`) on
    other predicates. Consider the following entity type and its table definition:
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

    Examples of creating selecters with predicates:
    @code{.cpp}
    // Selects entities where the name is not "Unknown".
    auto selecter = sqt::DataContext<MyEntity>::MakeSelecter().Where(
        sqt::Table<MyEntity>.name != "Unknown"
    );

    // Selects the entity with the primary key.
    auto selecter = sqt::DataContext<MyEntity>::MakeSelecter().Where(
        sqt::Table<MyEntity>.PrimaryKey == 100
    );

    // Selects the entity with the index.
    auto selecter = sqt::DataContext<MyEntity>::MakeSelecter().Where(
        sqt::Table<MyEntity>.Index_id_name == std::make_tuple(100, "Unknown")
    );

    // Selects entities with multiple conditions.
    auto selecter = sqt::DataContext<MyEntity>::MakeSelecter().Where(
        sqt::Table<MyEntity>.id < 100 && sqt::Table<MyEntity>.name != "Unknown"
    );
    @endcode

@see sqt::ExpressionLike
@see sqt::PredicateOperator
@see sqt::PredicateTermType
*/
template<typename T>
concept PredicateType = ExpressionLike<T> && requires {
    { T::Operator } -> std::same_as<const PredicateOperator&>;
};

}