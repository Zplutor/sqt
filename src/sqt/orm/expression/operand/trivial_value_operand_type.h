#pragma once

#include <sqt/orm/expression/operand/value_operand_type.h>
#include <sqt/orm/value/trivial/trivial_value_traits_type.h>

namespace sqt {

template<typename T>
concept TrivialValueOperandType = 
    ValueOperandType<T> && 
    TrivialValueTraitsType<typename T::ValueTraits>;

}