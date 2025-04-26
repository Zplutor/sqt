#pragma once

/**
@file
    Defines the `sqt::CompositeValueType` concept.
*/

#include <tuple>
#include <sqt/orm/value/trivial/basic/basic_value_type.h>

namespace sqt {
/** @cond */
namespace internal {
template<typename... T>
struct AreAllBasicValueTypes : std::false_type {};

template<>
struct AreAllBasicValueTypes<> : std::true_type {};

template<typename T, typename... Rest>
struct AreAllBasicValueTypes<T, Rest...> {
    static constexpr bool value = (BasicValueType<T>) && AreAllBasicValueTypes<Rest...>::value;
};

template<typename T>
struct IsCompositeValueType : std::false_type {};

template<typename... Types>
struct IsCompositeValueType<std::tuple<Types...>> {
    static constexpr bool value = AreAllBasicValueTypes<Types...>::value;
};
}
/** @endcond */


/**
Constrains a type to be a composite value type, which is a `std::tuple<>` of basic value types.

@details
    @b Requirements
    - The type must be a `std::tuple<>`.
    - All types in the tuple must satisfy the `sqt::BasicValueType` concept.

    Composite value types are used for primary keys and indexes that consist of multiple columns.

@see sqt::BasicValueType
*/
template<typename T>
concept CompositeValueType = internal::IsCompositeValueType<T>::value;

}