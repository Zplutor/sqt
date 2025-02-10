#pragma once

#include <sqt/foundation/statement.h>
#include <sqt/orm/value_type/value_type_traits.h>
#include <sqt/orm/table_mapping.h>

namespace sqt {

template<typename T>
concept EntityValueLike = requires {
    typename TableT<T>;
};

template<EntityValueLike T>
struct ValueTypeTraits<T> {

    static constexpr std::size_t ParameterCount = std::tuple_size<T>::value;

    static int BindValueToStatement(Statement& statement, int parameter_index, const T& value) {

    }

    static T GetValueFromStatement(const Statement& statement, int column_index) {

    }
};

}