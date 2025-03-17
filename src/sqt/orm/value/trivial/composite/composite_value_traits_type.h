#pragma once

#include <sqt/orm/value/trivial/composite/composite_value_type.h>
#include <sqt/orm/value/value_traits_type.h>

namespace sqt {

template<typename T>
concept CompositeValueTraitsType = 
    ValueTraitsType<T> && 
    CompositeValueType<typename T::ValueType> &&
    requires {
        typename T::ValueTraitsTypes;
    };

}