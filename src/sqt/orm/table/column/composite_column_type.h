#pragma once

#include <concepts>
#include <string>
#include <sqt/orm/table/column/value_source_type.h>

namespace sqt {

template<typename T>
concept CompositeColumnType = 
    requires {
        typename T::EntityType;
        typename T::ValueTraits;
        typename T::ValueType;
        typename T::ValueSource;
        { T::ColumnCount } -> std::same_as<const std::size_t&>;
        requires T::ColumnCount > 0;
        { T::BuildColumnNames() } -> std::same_as<std::string>;
    } && 
    ValueSourceType<typename T::ValueSource, typename T::EntityType>;

}