#pragma once

#include <sqt/orm/value/trivial/trivial_value_type.h>
#include <sqt/orm/value/value_traits_type.h>

namespace sqt {

template<typename T>
concept TrivialValueTraitsType = ValueTraitsType<T> && TrivialValueType<typename T::ValueType>;

}