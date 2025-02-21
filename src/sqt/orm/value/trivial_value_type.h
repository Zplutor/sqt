#pragma once

#include <sqt/orm/value/composite_value_type.h>

namespace sqt {

template<typename T>
concept TrivialValueType = PrimitiveValueType<T> || NullableValueType<T> || CompositeValueType<T>;

}