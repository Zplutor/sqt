#pragma once

#include <type_traits>
#include <sqt/orm/expression/expression_like.h>
#include <sqt/orm/expression/value_operand.h>

namespace sqt {

template<typename T>
concept ValueOperandLike = ExpressionLike<T> && std::is_base_of_v<ValueOperand, T>;

}