#pragma once

#include <sqt/orm/value/value_traits_type.h>

namespace sqt {

template<ValueTraitsType TRAITS>
class Binder {
public:
    using ValueTraits = TRAITS;
    using ValueType = typename TRAITS::ValueType;

public:
    constexpr Binder(int index) noexcept : index_(index) {

    }

    constexpr int Index() const noexcept {
        return index_;
    }

private:
    int index_{};
};

}