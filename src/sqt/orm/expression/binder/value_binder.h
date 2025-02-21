#pragma once

#include <sqt/foundation/statement.h>
#include <sqt/orm/value/trivial_value_traits.h>
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

    void Bind(Statement& statement, const ValueType& value) const {
        ValueTraits::BindValueToStatement(statement, index_, value);
    }

private:
    int index_{};
};

}