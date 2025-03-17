#pragma once

#include <sqt/orm/value/trivial/basic/custom_value_traits.h>

namespace sqt {

template<typename T>
concept CustomValueType = requires {
    { CustomValueTraits<T>::DataType };
};

}