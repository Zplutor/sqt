#pragma once

#include <sqt/foundation/data_type.h>
#include <sqt/orm/table/column/identifier_descriptor_type.h>

namespace sqt {

template<typename T>
concept ColumnDescriptorType = IdentifierDescriptorType<T> &&
    requires {
        { T::DataType } -> std::same_as<const DataType&>;
        { T::IsNullable } -> std::same_as<const bool&>;
    };

}