#pragma once

#include <sqt/orm/expression/identifier_operand_like.h>
#include <sqt/orm/expression/value_operand_like.h>

namespace sqt {

template<typename T>
concept AssignmentLike = 
    IdentifierOperandLike<typename T::IdentifierOperandType> &&
    ValueOperandLike<typename T::ValueOperandType>;

}