#pragma once

#include <sqt/orm/expression/operand/value_operand_type.h>
#include <sqt/orm/value/entity_value_traits_type.h>

namespace sqt {

template<typename T>
concept EntityValueOperandType = 
    ValueOperandType<T> && 
    EntityValueTraitsType<typename T::ValueTraits>;

}