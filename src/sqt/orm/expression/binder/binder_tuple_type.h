#pragma once

/**
@file
    Defines the `sqt::BinderTupleType` concept.
*/

#include <tuple>
#include <sqt/orm/expression/binder/binder_type.h>

namespace sqt {
/** @cond */
namespace internal {

template<typename T>
struct IsBinderTupleType : std::false_type {};

template<BinderType... TYPES>
struct IsBinderTupleType<std::tuple<TYPES...>> : std::true_type {};

}
/** @endcond */

/**
Constraints a type to be a `std::tuple` whose elements all satisfy the `sqt::BinderType` concept.

@details
    @b Requirements
    - The type is a `std::tuple`.
    - All elements of the tuple satisfy the `sqt::BinderType` concept; or the tuple is empty.

@see sqt::BinderType
*/
template<typename T>
concept BinderTupleType = internal::IsBinderTupleType<T>::value;

}