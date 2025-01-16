#pragma once

#include <format>
#include <string>
#include <string_view>
#include <sqt/orm/querier/selecter/limit_capacity.h>
#include <sqt/orm/querier/selecter/where_capacity.h>
#include <sqt/orm/table_mapping.h>
#include <sqt/orm/utility/utility.h>

namespace sqt {

template<typename SELECTER>
class PrimitiveSelecter : 
    public WhereCapacity<SELECTER>, 
    public LimitCapacity<SELECTER> {

public:
    static constexpr std::size_t ParameterIndex = 1;
    static constexpr std::size_t ParameterCount = 0;

    static constexpr std::tuple<> BuildPlaceholderBinders() {
        return std::tuple<>{};
    }

public:
    std::string_view BuildSQL() const {

        static const std::string sql = [this]() {
            const auto& selecter = static_cast<const SELECTER&>(*this);
            return std::format(
                "select {} from {}",
                JoinColumnNames(selecter.GetAbstractColumns()),
                TableV<SELECTER::EntityType>.GetName());
        }();

        return sql;
    }

    void BindInlineParameters(Statement&) const {

    }
};

}