#pragma once

#include <sqt/orm/value_type/composite_value_type.h>
#include <sqt/orm/value_type/nullable_value_type.h>
#include <sqt/orm/value_type/primitive_value_type.h>

namespace sqt {

template<typename T>
concept BindableValueType = PrimitiveValueType<T> || NullableValueType<T> || CompositeValueType<T>;

}