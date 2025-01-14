#pragma once

#include <sqt/orm/select/primitive_selecter.h>
#include <sqt/orm/table_mapping.h>

namespace sqt {

template<typename E>
class EntitySelecter : public PrimitiveSelecter<EntitySelecter<E>> {
public:
    using EntityType = E;

    static constexpr std::size_t ParameterIndex = 1;
    static constexpr std::size_t ParameterCount = 0;

public:
    constexpr EntitySelecter() noexcept = default;

private:
    friend class PrimitiveSelecter<EntitySelecter<E>>;

    AbstractColumnsView GetAbstractColumns() const {
        return TableV<EntityType>.GetAbstractColumns();
    }
};

}