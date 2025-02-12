#pragma once

#include <type_traits>
#include <sqt/orm/table/abstract_table.h>

namespace sqt {

template<typename T>
concept TableLike = std::is_base_of_v<AbstractTable, T> && requires {
    typename T::EntityType;
};

}