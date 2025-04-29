#pragma once

#include <array>
#include <sqt/orm/table/column/column.h>
#include <sqt/orm/table/column/column_type.h>
#include <sqt/orm/table_mapping.h>

namespace sqt::internal {

template<ColumnType... COLUMNS>
class ColumnArray;

template<ColumnType FIRST, ColumnType... REST>
class ColumnArray<FIRST, REST...> {
public:
    using EntityType = typename FIRST::EntityType;

    static constexpr std::size_t ColumnCount = 1 + sizeof...(REST);

    static constexpr std::array<const Column<EntityType>*, ColumnCount> Columns{
        Table<EntityType>.template GetColumn<FIRST>(),
        Table<EntityType>.template GetColumn<REST>()...
    };
};

template<ColumnType COLUMN>
class ColumnArray<COLUMN> {
public:
    using EntityType = typename COLUMN::EntityType;

    static constexpr std::size_t ColumnCount = 1;

    static constexpr std::array<const Column<EntityType>*, ColumnCount> Columns{
        Table<EntityType>.template GetColumn<COLUMN>()
    };
};

}