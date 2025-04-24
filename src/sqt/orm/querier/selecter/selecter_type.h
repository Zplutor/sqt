#pragma once

/**
@file
    Defines the `sqt::SelecterType` concept.
*/

#include <sqt/orm/querier/querier_type.h>

namespace sqt {

/**
Constrains a type to be a selecter type, which corresponds to a `SELECT` SQL statement that can be 
executed.

@details
    @b Requirements
    - The type must satisfy the `sqt::QuerierType` concept.
    - The type must have a static member type `ResultElementType`, which is the type of the result
      element.
    - The type must have a static method `GetResultElement()` with the following signature:
      @code{.cpp}
      static ResultElementType GetResultElement(sqt::Statement& statement);
      @endcode

    A selecter type is a specialized querier type that corresponds to a `SELECT` SQL statement.  
    This concept adds more constraints about getting the result elements from the statement.

@see sqt::QuerierType
*/
template<typename T>
concept SelecterType = QuerierType<T> && requires(Statement& statement) {
    typename T::ResultElementType;
    { T::GetResultElement(statement) } -> std::same_as<typename T::ResultElementType>;
};

}