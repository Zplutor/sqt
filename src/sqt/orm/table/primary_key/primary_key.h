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
    constexpr PrimaryKey() noexcept = default;

    AbstractColumnsView GetAbstractColumns() const noexcept override {
        return CompositeColumn<Columns...>::GetAbstractColumns();
    }
};


template<ColumnType... Columns>
PrimaryKey<Columns...> MakePrimaryKey(const Columns&... columns) {}

}