#pragma once

/**
@file
    Defines the `sqt::Binder<>` class template.
*/

#include <sqt/orm/value/value_traits_type.h>

namespace sqt {

/**
Provides information for binding values to a placeholder of an executor.

@tparam TRAITS
    The value traits type of the binder.

@details
    The `sqt::Binder<>` class template is used by the `sqt::BinderChain<>` class template to bind
    values to placeholders in an executor. It provides the necessary binding information, such as 
    the value traits type and the index of the placeholder.

    This class template satisfies the `sqt::BinderType` concept.
   
@see
    sqt::BinderType
*/
template<ValueTraitsType TRAITS>
class Binder {
public:
    using ValueTraits = TRAITS;
    using ValueType = typename TRAITS::ValueType;

public:
    /**
    Constructs a binder for the specified placeholder index.

    @param index
        The index of the placeholder to which the value will be bound.
    */
    constexpr Binder(int index) noexcept : index_(index) {

    }

    /**
    Gets the index of the placeholder.

    @return
        The index of the placeholder.
    */
    constexpr int Index() const noexcept {
        return index_;
    }

private:
    int index_{};
};

}