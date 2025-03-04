#pragma once

#include <sqt/orm/expression/operand/identifier_operand.h>
#include <sqt/orm/expression/operand/value_operand.h>
#include <sqt/orm/value/trivial_value_traits.h>
#include <sqt/orm/value/trivial_value_type.h>

namespace sqt {

template<ColumnType T>
constexpr auto MakeOperand(const T&) {
    return IdentifierOperand<T>{};
}


template<CompositeColumnType T>
constexpr auto MakeOperand(const T&) {
    return IdentifierOperand<T>{};
}


template<TrivialValueType T>
constexpr auto MakeOperand(const T& value) {
    using Traits = TrivialValueTraits<T>;
    using Operand = ValueOperand<Traits>;
    return Operand{ value };
}

}