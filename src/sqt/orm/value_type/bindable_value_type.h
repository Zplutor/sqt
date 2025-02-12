#pragma once

#include <sqt/orm/value_type/composite_value_type.h>
#include <sqt/orm/value_type/entity_value_type.h>
#include <sqt/orm/value_type/nullable_value_type.h>
#include <sqt/orm/value_type/primitive_value_type.h>

namespace sqt {

template<typename T>
concept BindableValueType = 
    PrimitiveValueLike<T> || NullableValueLike<T> || CompositeValueLike<T> || EntityValueLike<T>;

}