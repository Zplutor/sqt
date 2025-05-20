#pragma once

/**
@file
    Defines the `sqt::IdentifierBinderType` concept.
*/

#include <sqt/orm/expression/binder/binder_type.h>
#include <sqt/orm/value/identifier/identifier_value_traits_type.h>

namespace sqt {

/**
Constrains a type to be a binder type that associated with an identifier type.

@details
    @b Requirements
    - The type must satisfy the `sqt::BinderType` concept.
    - The nested type `ValueTraits` of the type must satisfy the `sqt::IdentifierValueTraitsType` 
      concept.

@see sqt::BinderType
*/
template<typename T>
concept IdentifierBinderType = 
    BinderType<T> && 
    IdentifierValueTraitsType<typename T::ValueTraits>;

}