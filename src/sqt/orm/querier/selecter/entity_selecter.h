#pragma once

#include <sqt/orm/querier/selecter/primitive_selecter.h>
#include <sqt/orm/table_mapping.h>
#include <sqt/orm/utility/utility.h>

namespace sqt {

template<typename E>
class EntitySelecter : public PrimitiveSelecter<EntitySelecter<E>> {
public:
    using EntityType = E;
    using ResultElementType = E;

    static E GetResultElement(Statement& statement) {
        return {};
    }

public:
    constexpr EntitySelecter() noexcept = default;

private:
    friend class PrimitiveSelecter<EntitySelecter<E>>;

    static std::string BuildColumnNames() {
        return JoinColumnNames(TableV<EntityType>.GetAbstractColumns());
    }
};

}