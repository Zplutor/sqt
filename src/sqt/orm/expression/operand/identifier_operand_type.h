#pragma once

/**
@file
    Defines the `sqt::IdentifierOperandType` concept.
*/

#include <type_traits>
#include <sqt/orm/expression/operand/operand_type.h>

namespace sqt {

/**
Constrains a type to be an identifier operand type.

@details
    @b Requirements
    - The type must satisfy the `sqt::OperandType` concept.
    - The type must have a nested type `IdentifierType`, which is the type of the identifier
      represented by the operand.

    Identifier operands are used to represent identifiers in expressions, such as columns, primary
    keys or indexes. The specializations of the `sqt::IdentifierOperand<>` template satisfy this
    concept.

@see sqt::IdentifierOperand<>
@see sqt::IdentifierOperand<COLUMN>
@see sqt::IdentifierOperand<COMPOSITE_COLUMN>
@see sqt::OperandType
*/
template<typename T>
concept IdentifierOperandType = OperandType<T> && requires {
    typename T::IdentifierType;
};

}