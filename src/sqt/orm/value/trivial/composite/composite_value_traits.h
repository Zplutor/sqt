#pragma once

#include <tuple>
#include <sqt/orm/value/trivial/basic/basic_value_traits_type.h>

namespace sqt {

template<BasicValueTraitsType... TRAITS>
class CompositeValueTraits {
public:
    static_assert(sizeof...(TRAITS) > 0);

    using ValueTraitsTypes = std::tuple<TRAITS...>;
    using ValueType = std::tuple<typename TRAITS::ValueType...>;

    static void BindValue(Statement& statement, int parameter_index, const ValueType& value) {

        std::apply(
            [&statement, parameter_index](const auto&... values) {
                int index = parameter_index;
                (TRAITS::BindValue(statement, index++, values), ...);
            },
            value);
    }

    static ValueType RetrieveValue(const Statement& statement, int column_index) {

        int index = column_index;
        return ValueType{ TRAITS::RetrieveValue(statement, index++)... };
    }
};

}