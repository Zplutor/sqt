#pragma once

#include <sqt/orm/value/trivial/basic/primitive_value_traits.h>
#include <sqt/orm/value/trivial/basic/primitive_value_type.h>
#include <sqt/orm/value/trivial/basic/nullable_value_traits.h>
#include <sqt/orm/value/trivial/basic/nullable_value_type.h>
#include <sqt/orm/value/trivial/basic/custom_value_traits.h>
#include <sqt/orm/value/trivial/basic/custom_value_type.h>

namespace sqt {

template<typename T>
class BasicValueTraitsFor;


template<PrimitiveValueType T>
class BasicValueTraitsFor<T> {
public:
    using type = PrimitiveValueTraits<T>;
};


template<NullableValueType T>
class BasicValueTraitsFor<T> {
public:
    using type = NullableValueTraits<T>;
};


template<CustomValueType T>
class BasicValueTraitsFor<T> {
public:
    using type = CustomValueTraits<T>;
};


template<typename T>
using BasicValueTraitsForT = typename BasicValueTraitsFor<T>::type;

}