#pragma once

#include <sqt/orm/table/abstract_primary_key.h>
#include <sqt/orm/table/composite_column.h>

namespace sqt {

template<ColumnLike... Columns>
class PrimaryKey : public CompositeColumn<Columns...>, public AbstractPrimaryKey {
    static_assert(
        !(Columns::ValueTraits::IsNullable && ...),
        "Primary key columns cannot be nullable.");

public:
    using CompositeColumn<Columns...>::CompositeColumn;

    AbstractColumnsView GetAbstractColumns() const noexcept override {
        return CompositeColumn<Columns...>::GetAbstractColumns();
    }
};


template<ColumnLike... Columns>
PrimaryKey<Columns...> MakePrimaryKey(const Columns&... columns) {}

}