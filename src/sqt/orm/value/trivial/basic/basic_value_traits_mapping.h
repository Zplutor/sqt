#pragma once

/**
@file
    Defines the `sqt::BasicValueTraitsMapping<>` class template specializations for various basic
    value types.
*/

#include <sqt/orm/value/trivial/basic/primitive_value_traits.h>
#include <sqt/orm/value/trivial/basic/primitive_value_type.h>
#include <sqt/orm/value/trivial/basic/nullable_value_traits.h>
#include <sqt/orm/value/trivial/basic/nullable_value_type.h>
#include <sqt/orm/value/trivial/basic/custom_value_traits.h>
#include <sqt/orm/value/trivial/basic/custom_value_type.h>

namespace sqt {

/**
Maps a basic value type to its corresponding value traits type.

@tparam T
    The basic value type to map. It must satisfy the `sqt::BasicValueType` concept.

@details
    The mapped value traits type is defined as a nested type `type`. Depending on the value type
    provided, `type` will be one of the following:
    - `sqt::PrimitiveValueTraits<>` for primitive value types.
    - `sqt::NullableValueTraits<>` for nullable value types.
    - `sqt::CustomValueTraits<>` for custom value types.

@see sqt::BasicValueType
@see sqt::CustomValueTraits<>
@see sqt::PrimitiveValueTraits<>
@see sqt::NullableValueTraits<>
*/
template<typename T>
class BasicValueTraitsMapping;

/** @cond */
template<PrimitiveValueType T>
class BasicValueTraitsMapping<T> {
public:
    using type = PrimitiveValueTraits<T>;
};


template<NullableValueType T>
class BasicValueTraitsMapping<T> {
public:
    using type = NullableValueTraits<T>;
};


template<CustomValueType T>
class BasicValueTraitsMapping<T> {
public:
    using type = CustomValueTraits<T>;
};
/** @endcond */


/**
A helper type alias for getting the mapped value traits type from `sqt::BasicValueTraitsMapping<>`.

@tparam T
    The basic value type.

@relates sqt::BasicValueTraitsMapping
*/
template<typename T>
using BasicValueTraitsMappingT = typename BasicValueTraitsMapping<T>::type;

}