#pragma once

#include <concepts>
#include <sqt/orm/table/column/abstract_column.h>
#include <sqt/orm/table/column/value_source_type.h>

namespace sqt {

template<typename T>
concept ColumnType = 
    std::is_base_of_v<AbstractColumn, T> && 
    requires {
        typename T::EntityType;
        typename T::ValueType;
        typename T::ValueTraits;
        typename T::ValueSource;
        { T::Name } -> std::same_as<const std::string_view&>;
    } && 
    ValueSourceType<typename T::ValueSource, typename T::EntityType>;
}