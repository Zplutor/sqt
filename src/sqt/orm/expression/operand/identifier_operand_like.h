#pragma once

#include <type_traits>
#include <sqt/orm/expression/expression_like.h>
#include <sqt/orm/expression/operand/identifier_operand.h>

namespace sqt {

template<typename T>
concept IdentifierOperandLike = 
    std::is_base_of_v<IdentifierOperand, T> && 
    ExpressionLike<T> &&
    requires {
        typename T::EntityType;
    };

}