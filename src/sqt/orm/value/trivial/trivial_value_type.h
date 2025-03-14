#pragma once

#include <sqt/orm/value/trivial/composite/composite_value_type.h>

namespace sqt {

template<typename T>
concept TrivialValueType = PrimitiveValueType<T> || NullableValueType<T> || CompositeValueType<T>;

}