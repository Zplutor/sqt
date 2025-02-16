#pragma once

#include <sqt/orm/table_mapping.h>

namespace sqt {

template<typename T>
concept EntityValueLike = requires {
    typename Table<T>::type;
};

}