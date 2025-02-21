#pragma once

#include <sqt/orm/value/entity_value_type.h>
#include <sqt/orm/value/value_traits_type.h>

namespace sqt {

template<typename T>
concept EntityValueTraitsType = ValueTraitsType<T> && EntityValueType<typename T::ValueType>;

}