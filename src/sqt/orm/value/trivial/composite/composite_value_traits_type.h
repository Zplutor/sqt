#pragma once

/**
@file
    Defines the `sqt::CompositeValueTraitsType` concept.
*/

#include <sqt/orm/value/trivial/composite/composite_value_type.h>
#include <sqt/orm/value/value_traits_type.h>

namespace sqt {

/**
Constrains a type to be a composite value traits type, which defines traits for a composite value 
type.

@details
    @b Requirements
    - The type must satisfy the `sqt::ValueTraitsType` concept.
    - The nested type `ValueType` must satisfy the `sqt::CompositeValueType` concept.
    - There must be a nested type `ValueTraitsTypes` that is a tuple of value traits types for each
      element in the composite value type.

    Composite value traits types are used by the framework to interact with composite value types. 
    The `sqt::CompositeValueTraits<>` class template satisfies this concept.

@see sqt::CompositeValueTraits<>
@see sqt::CompositeValueType
@see sqt::ValueTraitsType
*/
template<typename T>
concept CompositeValueTraitsType = 
    ValueTraitsType<T> && 
    CompositeValueType<typename T::ValueType> &&
    requires {
        typename T::ValueTraitsTypes;
    };

}