#pragma once

#include <format>
#include <string>
#include <string_view>
#include <sqt/orm/select/limit_selecter.h>
#include <sqt/orm/table_mapping.h>
#include <sqt/orm/utility/utility.h>

namespace sqt {

template<typename Selecter>
class PrimitiveSelecter {
public:
    static constexpr std::tuple<> BuildPlaceholderBinders() {
        return std::tuple<>{};
    }

public:
    std::string_view BuildSQL() const {

        static const std::string sql = [this]() {
            const auto& selecter = static_cast<const Selecter&>(*this);
            return std::format(
                "select {} from {}",
                JoinColumnNames(selecter.GetAbstractColumns()),
                TableV<Selecter::EntityType>.GetName());
        }();

        return sql;
    }

    void BindInlineParameters(Statement&) const {

    }

    constexpr auto Limit(std::size_t limit) const {
        return LimitSelecter<Selecter, Operand<std::size_t>>{
            static_cast<const Selecter&>(*this), 
            Operand<std::size_t>{ limit }
        };
    }

    constexpr auto Limit(PlaceholderTag) const {
        return LimitSelecter<Selecter, Operand<Placeholder<std::size_t>>> {
            static_cast<const Selecter&>(*this),
            Operand<Placeholder<std::size_t>>{},
        };
    }
};

}