#pragma once

#include <sqt/core/statement.h>
#include <sqt/orm/value_type/bindable_value_type.h>

namespace sqt {

template<BindableValueType V>
class ValueBinder {
public:
    using ValueType = V;

public:
    constexpr ValueBinder(int index) : index_(index) {

    }

    void Bind(Statement& statement, const ValueType& value) {
        ValueTypeTraits<V>::BindValueToStatement(statement, index_, value);
    }

private:
    int index_{};
};

}