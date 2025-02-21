#pragma once

#include <sqt/orm/expression/identifier_operand_like.h>
#include <sqt/orm/expression/value_operand_type.h>

namespace sqt {

template<typename T>
concept AssignmentLike = 
    IdentifierOperandLike<typename T::IdentifierOperandType> &&
    ValueOperandType<typename T::ValueOperandType>;

}