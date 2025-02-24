#pragma once

#include <sqt/orm/table/column.h>
#include <sqt/orm/value/entity_value_type.h>
#include <sqt/orm/value/value_traits_type.h>

namespace sqt {

template<typename T>
concept EntityValueTraitsType = 
    ValueTraitsType<T> && 
    EntityValueType<typename T::ValueType> && 
    requires {
        typename T::EntityType;
        typename T::TableType;
        { T::InsertingColumns } -> std::same_as<const ColumnsView<typename T::EntityType>&>;
    };

}