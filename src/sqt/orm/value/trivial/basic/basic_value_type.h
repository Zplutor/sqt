#pragma once

#include <sqt/orm/value/trivial/basic/custom_value_type.h>
#include <sqt/orm/value/trivial/basic/nullable_value_type.h>
#include <sqt/orm/value/trivial/basic/primitive_value_type.h>

namespace sqt {

template<typename T>
concept BasicValueType = PrimitiveValueType<T> || NullableValueType<T> || CustomValueType<T>;

}