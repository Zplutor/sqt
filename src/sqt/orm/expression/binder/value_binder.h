#pragma once

#include <sqt/foundation/statement.h>
#include <sqt/orm/value/traits/identifier_value_traits_type.h>
#include <sqt/orm/value/traits/trivial_value_traits.h>
#include <sqt/orm/value/traits/value_traits_type.h>

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
        ValueTraits::BindValue(statement, index_, value);
    }

    template<typename T = ValueTraits>
    void BindFromEntity(Statement& statement, const typename T::EntityType& entity) const
        requires IdentifierValueTraitsType<T> {

        T::BindFromEntity(statement, index_, entity);
    }

private:
    int index_{};
};

}