#pragma once

#include <type_traits>
#include <sqt/orm/table/abstract_column.h>

namespace sqt {

template<typename T>
concept ColumnType = std::is_base_of_v<AbstractColumn, T> && requires {
    typename T::EntityType;
    typename T::ValueType;
    { T::Name } -> std::same_as<const std::string_view&>;
};

}