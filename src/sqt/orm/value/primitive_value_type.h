#pragma once

#include <sqt/orm/value/data_type_mapping.h>

namespace sqt {

template<typename T>
concept PrimitiveValueType = requires {
    { MapToDataType<T>::value } -> std::same_as<const DataType&>;
};

}