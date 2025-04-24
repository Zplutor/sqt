#pragma once

/**
@file
    Defines the `sqt::ValueTraitsType` concept.
*/

#include <concepts>
#include <sqt/foundation/statement.h>

namespace sqt {

/**
Constrains a type to be a value traits type, which is used to interact with its corresponding value 
type.

@details
    @b Requirements
    - The type must have a nested type `ValueType`, which represents the type of the value.
    - The type must have a static method `BindValue()` with the following signature:
      @code{.cpp}
      static void BindValue(sqt::Statement& statement, int param_index, const ValueType& value);
      @endcode
    - The type must have a static method `RetrieveValue()` with the following signature:
      @code{.cpp}
      static ValueType RetrieveValue(const sqt::Statement& statement, int column_index);
      @endcode

    Value traits types provide the information and operations needed by the framework to interact
    with the corresponding value types, such as binding parameters and retrieving results from
    SQL statements.

    This concept defines the least restrictive set of requirements for value traits types; 
    more specific concepts exist for specialized value traits types. The following diagram shows 
    the relationships among different concepts for value traits types:

    @dot
    digraph {
        rankdir=LR;
        edge [dir=back,arrowtail=onormal];
        node [shape=record];
        ValueTraitsType -> { 
            TrivialValueTraitsType 
            IdentifierValueTraitsType 
            EntityValueTraitsType  
        };
        TrivialValueTraitsType -> {
            BasicValueTraitsType
            CompositeValueTraitsType
        };
    }
    @enddot

@see sqt::BasicValueTraitsType
@see sqt::CompositeValueTraitsType
@see sqt::EntityValueTraitsType
@see sqt::IdentifierValueTraitsType
@see sqt::TrivialValueTraitsType
*/
template<typename T>
concept ValueTraitsType = 
    requires {
        typename T::ValueType;
    } &&
    requires (Statement& statement, int parameter_index, const typename T::ValueType& value) {
        { T::BindValue(statement, parameter_index, value) } -> std::same_as<void>;
    } &&
    requires (const Statement& statement, int column_index) {
        { T::RetrieveValue(statement, column_index) } -> 
            std::same_as<typename T::ValueType>;
    };
}