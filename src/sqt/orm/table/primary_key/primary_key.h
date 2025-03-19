#pragma once

#include <sqt/orm/table/primary_key/abstract_primary_key.h>
#include <sqt/orm/table/column/composite_column.h>

namespace sqt {

template<ColumnType... Columns>
class PrimaryKey : public CompositeColumn<Columns...>, public AbstractPrimaryKey {
    static_assert(
        !(Columns::ValueTraits::IsNullable && ...),
        "Primary key columns cannot be nullable.");

public:
    constexpr explicit PrimaryKey(const Columns&... columns) : 
        CompositeColumn<Columns...>(columns...),
        column_indexes_({ columns.GetIndex()... }) {

    }

    constexpr std::span<const std::size_t> GetColumnIndexes() const noexcept {
        return column_indexes_;
    }

    AbstractColumnsView GetAbstractColumns() const noexcept override {
        return CompositeColumn<Columns...>::GetAbstractColumns();
    }

private:
    std::array<std::size_t, sizeof...(Columns)> column_indexes_;
};


template<ColumnType... Columns>
PrimaryKey<Columns...> MakePrimaryKey(const Columns&... columns) {}

}