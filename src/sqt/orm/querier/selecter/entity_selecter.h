#pragma once

#include <sqt/orm/querier/selecter/base_selecter.h>
#include <sqt/orm/table_mapping.h>
#include <sqt/orm/utility/utility.h>
#include <sqt/orm/value/entity/entire_entity_value_traits.h>
#include <sqt/orm/value/entity/entity_value_type.h>

namespace sqt {

template<EntityValueType ENTITY>
class EntitySelecter : public BaseSelecter<EntitySelecter<ENTITY>> {
public:
    using EntityType = ENTITY;
    using ResultElementType = ENTITY;

    static ENTITY GetResultElement(Statement& statement) {
        return EntireEntityValueTraits<ENTITY>::RetrieveValue(statement, 0);
    }

public:
    constexpr EntitySelecter() noexcept = default;

private:
    friend class BaseSelecter<EntitySelecter<ENTITY>>;

    static std::string BuildColumnNames() {
        return JoinColumnNames(EntireEntityValueTraits<ENTITY>::ManipulatingColumns);
    }
};

}