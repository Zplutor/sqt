#pragma once

#include <sqt/orm/value/trivial/basic/primitive_value_traits.h>

namespace sqt {

template<typename T>
concept PrimitiveValueType = requires {
    { PrimitiveValueTraits<T>::DataType };
};

}