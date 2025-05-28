#pragma once

/**
@file
    Defines the `sqt::OrderingTermType` concept.
*/

#include <sqt/orm/expression/expression_like.h>
#include <sqt/orm/expression/ordering.h>

namespace sqt {

/**
Constrains a type to be an ordering term type, which is used in the `ORDER BY` clause.

@details
    @b Requirements
    - The type must satisfy the `sqt::ExpressionLike` concept.
    - The type must have a static constant `OrderingValue` of type `sqt::Ordering`, representing 
      the ordering.

    Ordering terms are used by the `sqt::OrderBySelectDecorator<>` to determine the ordering of the
    selected results.

    To create ordering terms, use the `Asc()` and `Desc()` method of identifiers (including 
    columns, primary keys and indexes). Consider the following entity type and its table 
    definition:

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

    Examples of creating selecters with ordering terms:
    @code{.cpp}
    // Order by a column in ascending order.
    auto selecter = sqt::DataContext<MyEntity>::MakeSelecter().OrderBy(
        sqt::Table<MyEntity>.id.Asc()
    );

    // Order by two columns in different order.
    auto selecter = sqt::DataContext<MyEntity>::MakeSelecter().OrderBy(
        sqt::Table<MyEntity>.id.Asc(),
        sqt::Table<MyEntity>.name.Desc()
    );

    // Order by the primary key in ascending order.
    auto selecter = sqt::DataContext<MyEntity>::MakeSelecter().OrderBy(
        sqt::Table<MyEntity>.PrimaryKey.Asc()
    );

    // Order by an index in descending order.
    auto selecter = sqt::DataContext<MyEntity>::MakeSelecter().OrderBy(
        sqt::Table<MyEntity>::Index_id_name.Desc()
    );
    @endcode

    The `sqt::OrderingTerm<>` class template satisfies this concept.

@see sqt::ExpressionLike
@see sqt::Ordering
*/
template<typename T>
concept OrderingTermType = ExpressionLike<T> && requires {
    { T::OrderingValue } -> std::same_as<const Ordering&>;
};

}
