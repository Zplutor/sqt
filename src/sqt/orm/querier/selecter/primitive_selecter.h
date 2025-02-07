#pragma once

#include <format>
#include <string>
#include <string_view>
#include <sqt/orm/querier/selecter/limit_capacity.h>
#include <sqt/orm/querier/selecter/where_capacity.h>
#include <sqt/orm/table_mapping.h>

namespace sqt {

template<typename SELECTER>
class PrimitiveSelecter : 
    public WhereCapacity<SELECTER>, 
    public LimitCapacity<SELECTER> {

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

    static constexpr std::tuple<> BuildPlaceholderBinders() {
        return std::tuple<>{};
    }

public:
    void BindInlineParameters(Statement&) const {

    }
};

}