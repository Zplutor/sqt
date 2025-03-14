#pragma once

#include <concepts>
#include <sqt/foundation/data_type.h>
#include <sqt/orm/value/traits/value_traits_type.h>

namespace sqt {

template<typename T>
concept BasicValueTraitsType = ValueTraitsType<T> && requires {
    { T::DataType } -> std::same_as<const DataType&>;
    { T::IsNullable } -> std::same_as<const bool&>;
    requires T::ParameterCount == 1;
};

}