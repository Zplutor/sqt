#pragma once

#include <type_traits>
#include <sqt/orm/column/abstract_column.h>

namespace sqt {

template<typename T>
concept ColumnLike = std::is_base_of_v<AbstractColumn, T> && requires {
    typename T::EntityType;
    typename T::ValueType;
};

}