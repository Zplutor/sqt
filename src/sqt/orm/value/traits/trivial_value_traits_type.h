#pragma once

#include <sqt/orm/value/trivial_value_type.h>
#include <sqt/orm/value/traits/value_traits_type.h>

namespace sqt {

template<typename T>
concept TrivialValueTraitsType = ValueTraitsType<T> && TrivialValueType<typename T::ValueType>;

}