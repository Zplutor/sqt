#pragma once

#include <string>
#include <type_traits>
#include <sqt/core/data_type.h>

namespace sqt {

template<typename T, typename = void>
struct MapToDataType;

template<typename T>
struct MapToDataType<T, std::enable_if_t<std::is_integral_v<T>>> {
    static constexpr DataType value = DataType::Integer;
};

template<typename T>
struct MapToDataType<T, std::enable_if_t<std::is_floating_point_v<T>>> {
    static constexpr DataType value = DataType::Float;
};

template<>
struct MapToDataType<std::string> {
    static constexpr DataType value = DataType::Text;
};

template<typename T>
constexpr DataType MapToDataTypeV = MapToDataType<T>::value;

}