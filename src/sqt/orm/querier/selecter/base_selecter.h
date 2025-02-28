#pragma once

#include <format>
#include <string>
#include <string_view>
#include <sqt/orm/querier/selecter/limit_select_capability.h>
#include <sqt/orm/querier/selecter/where_select_decorator.h>
#include <sqt/orm/querier/where_capability.h>
#include <sqt/orm/table_mapping.h>

namespace sqt {

template<typename SELECTER>
class BaseSelecter : 
    public WhereCapability<SELECTER, WhereSelectDecorator>,
    public LimitSelectCapability<SELECTER> {

public:
    static constexpr std::size_t ParameterIndex = 1;
    static constexpr std::size_t ParameterCount = 0;

    static std::string_view BuildSQL() {

        static const std::string sql = std::format(
            "select {} from {}",
            SELECTER::BuildColumnNames(),
            TableV<SELECTER::EntityType>.GetName());

        return sql;
    }

    static constexpr auto BuildPlaceholderBinders() noexcept {
        return std::tuple<>{};
    }

public:
    constexpr void BindInlineParameters(Statement&) const noexcept {

    }
};

}