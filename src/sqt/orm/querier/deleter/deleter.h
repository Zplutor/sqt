#pragma once

#include <format>
#include <string_view>
#include <sqt/foundation/statement.h>
#include <sqt/orm/querier/where_capability.h>
#include <sqt/orm/table_mapping.h>
#include <sqt/orm/value/entity/entity_value_type.h>

namespace sqt {

template<EntityValueType ENTITY>
class Deleter : public WhereCapability<Deleter<ENTITY>> {
public:
    static constexpr std::size_t ParameterIndex = 1;
    static constexpr std::size_t ParameterCount = 0;

    static std::string_view BuildSQL() {
        static const std::string sql = []() {
            return std::format("delete from {}", TableV<ENTITY>.GetName());
        }();
        return sql;
    }

    static constexpr auto BuildPlaceholderBinders() noexcept {
        return std::tuple<>{};
    }

public:
    constexpr Deleter() = default;

    constexpr void BindInlineParameters(Statement&) const noexcept {

    }
};

}