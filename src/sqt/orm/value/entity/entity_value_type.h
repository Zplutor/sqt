#pragma once

#include <sqt/orm/table_mapping.h>

namespace sqt {

template<typename T>
concept EntityValueType = requires {
    typename TableMapping<T>::type;
};


template<typename T>
concept PrimaryKeyEntityValueType = EntityValueType<T> && requires {
    typename TableType<T>::PrimaryKeyType;
};


template<typename T>
concept AutoIncEntityValueType = PrimaryKeyEntityValueType<T> && requires {
    requires Table<T>.PrimaryKey.IsAutoInc();
};

}