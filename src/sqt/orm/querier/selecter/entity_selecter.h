#pragma once

#include <sqt/orm/querier/selecter/primitive_selecter.h>
#include <sqt/orm/table_mapping.h>

namespace sqt {

template<typename E>
class EntitySelecter : public PrimitiveSelecter<EntitySelecter<E>> {
public:
    using EntityType = E;

public:
    constexpr EntitySelecter() noexcept = default;

private:
    friend class PrimitiveSelecter<EntitySelecter<E>>;

    AbstractColumnsView GetAbstractColumns() const {
        return TableV<EntityType>.GetAbstractColumns();
    }
};

}