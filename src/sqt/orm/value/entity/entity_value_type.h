#pragma once

#include <sqt/orm/table_mapping.h>

namespace sqt {

template<typename T>
concept EntityValueType = requires {
    typename Table<T>::type;
};


template<typename T>
concept PrimaryKeyEntityValueType = EntityValueType<T> && requires {
    typename TableT<T>::PrimaryKeyType;
};


template<typename T>
concept AutoIncEntityValueType = PrimaryKeyEntityValueType<T> && requires {
    requires TableV<T>.PrimaryKey.IsAutoInc();
};

}