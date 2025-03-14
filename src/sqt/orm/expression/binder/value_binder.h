#pragma once

#include <sqt/orm/value/value_traits_type.h>

namespace sqt {

template<ValueTraitsType TRAITS>
class ValueBinder {
public:
    using ValueTraits = TRAITS;
    using ValueType = typename TRAITS::ValueType;

public:
    constexpr ValueBinder(int index) : index_(index) {

    }

    constexpr int GetIndex() const noexcept {
        return index_;
    }

private:
    int index_{};
};

}