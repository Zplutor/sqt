#pragma once

/**
@file
    Defines the `sqt::BinderType` concept.
*/

#include <concepts>

namespace sqt {

/**
Constrains a type to be a binder type, which provides information for binding values to a 
placeholder of an executor.

@details
    @b Requirements
    - The type must have a nested type `ValueType`.
    - The type must have a nested type `ValueTraits`.
    - The type must have a member method `Index()` with the following signature:
      @code
      int Index() const noexcept;
      @endcode

    The `sqt::Binder<>` class template satisfies this concept.

@see sqt::Binder<>
*/
template<typename T>
concept BinderType = requires {
    typename T::ValueType;
    typename T::ValueTraits;
} &&
requires(const T& t) {
    { t.Index() } noexcept -> std::same_as<int>;
};

}