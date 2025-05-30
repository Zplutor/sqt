#pragma once

/**
@file
    Defines the `sqt::EntityValueOperandType` concept.
*/

#include <sqt/orm/expression/operand/value_operand_type.h>
#include <sqt/orm/value/entity/entity_value_traits_type.h>

namespace sqt {

/**
Constrains a type to be a value operand type whose value type is an entity.

@details
    @b Requirements
    - The type must satisfy the `sqt::ValueOperandType` concept.
    - The nested type `ValueTraits` must satisfy the `sqt::EntityValueTraitsType` concept.

    This concept is used in some circumstances where the value operand is expected to represent an 
    entity value, such as in the inserter and updater that operate on entities.

@see sqt::EntityValueTraitsType
@see sqt::ValueOperandType
*/
template<typename T>
concept EntityValueOperandType = 
    ValueOperandType<T> && 
    EntityValueTraitsType<typename T::ValueTraits>;

}