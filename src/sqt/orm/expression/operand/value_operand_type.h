#pragma once

/**
@file
    Defines the `sqt::ValueOperandType` concept.
*/

#include <type_traits>
#include <sqt/orm/expression/operand/operand_type.h>

namespace sqt {

/**
Constrains a type to be a value operand type.

@details
    @b Requirements
    - The type must satisfy the `sqt::OperandType` concept.
    - The type must have a nested type `ValueType`, which is the type of the value represented by 
      the operand.
    - The type must have a nested type `ValueTraits`, which is the traits type for the value.
    
    Value operands are used to represent values in expressions, such as constants or placeholders.
    The following types satisfy this concept:
    - `sqt::ConstantOperand<>` for constant values.
    - `sqt::PlaceholderOperand<>` for placeholder values.

@see sqt::ConstantOperand<>
@see sqt::OperandType
@see sqt::PlaceholderOperand<>
*/
template<typename T>
concept ValueOperandType = OperandType<T> && requires {
    typename T::ValueTraits;
    typename T::ValueType;
};

}