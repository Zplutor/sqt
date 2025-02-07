#pragma once

#include <tuple>
#include <sqt/foundation/statement.h>
#include <sqt/orm/expression/assignment.h>
#include <sqt/orm/querier/inserter/conflict_action.h>

namespace sqt {

template<ConflictAction CONFLICT_ACTION, typename... ASSIGNMENT>
class Inserter {
public:
    static constexpr std::size_t ParameterIndex = 0;
    static constexpr std::size_t ParameterCount = 0;

    static constexpr auto BuildPlaceholderBinders() {

    }

public:
    constexpr Inserter(ASSIGNMENT... assignments) : assignments_(std::move(assignments)) {

    }

    std::string_view BuildSQL() const {
        static const std::string sql = []() {
            
        };
        return sql;
    }

    void BindInlineParameters(Statement& statement) const {

    }

private:
    std::tuple<ASSIGNMENT...> assignments_;
};

}