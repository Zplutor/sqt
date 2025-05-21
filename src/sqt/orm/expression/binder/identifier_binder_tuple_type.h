#pragma once

/**
@file
    Defines the `sqt::IdentifierBinderTupleType` concept.
*/

#include <tuple>
#include <sqt/orm/expression/binder/identifier_binder_type.h>

namespace sqt {
/** @cond */
namespace internal {

template<typename T>
struct IsIdentifierBinderTupleType : std::false_type {};

template<IdentifierBinderType... TYPES>
struct IsIdentifierBinderTupleType<std::tuple<TYPES...>> : std::true_type {};

}
/** @endcond */

/**
Constrains a type to be a `std::tuple` whose elements all satisfy the `sqt::IdentifierBinderType` 
concept.

@details
    @b Requirements
    - The type must be a `std::tuple`.
    - All elements of the tuple must satisfy the `sqt::IdentifierBinderType` concept; or the tuple 
    must be empty.

@see sqt::IdentifierBinderType
*/
template<typename T>
concept IdentifierBinderTupleType = internal::IsIdentifierBinderTupleType<T>::value;

}