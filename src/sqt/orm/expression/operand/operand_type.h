#pragma once

/**
@file
    Defines the `sqt::OperandType` concept.
*/

#include <sqt/orm/expression/expression_like.h>

namespace sqt {

/**
Constrains a type to be an operand type.

@details
    @b Requirements
    - The type must satisfy the `sqt::ExpressionLike` concept.

    Operands are used in expressions to represent values or identifiers. This concept defines the 
    common requirements for operand types. There are several concepts for more specific operand 
    types defined in the framework:
    - `sqt::ValueOperandType` for value operands.
    - `sqt::IdentifierOperandType` for identifier operands.

@see sqt::ExpressionLike
@see sqt::IdentifierOperandType
@see sqt::ValueOperandType
*/
template<typename T>
concept OperandType = ExpressionLike<T>;

}