#pragma once

/**
@file
    Defines the `sqt::CustomValueType` concept.
*/

#include <sqt/orm/value/trivial/basic/custom_value_traits.h>

namespace sqt {

/**
Constrains a type to be a custom value type, which is provided by the user.

@details
    @b Requirements
    - There must be a `sqt::CustomValueTraits<>` specialization for the type. The specialization is
      defined by the user.

    Custom value types are a subset of basic value types, which are constrained by the 
    `sqt::BasicValueType` concept.

@see sqt::BasicValueType
@see sqt::CustomValueTraits<>
*/
template<typename T>
concept CustomValueType = requires {
    { CustomValueTraits<T>::DataType };
};

}