#pragma once

#include <sqt/orm/expression/expression_like.h>

namespace sqt {

template<typename T>
concept OperandType = ExpressionLike<T>;

}