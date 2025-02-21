#pragma once

#include <type_traits>
#include <sqt/orm/expression/operand/operand_type.h>

namespace sqt {

template<typename T>
concept ValueOperandType = OperandType<T> && requires {
    typename T::ValueTraits;
    typename T::ValueType;
};

}