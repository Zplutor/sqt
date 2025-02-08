#pragma once

#include <tuple>
#include <sqt/foundation/statement.h>
#include <sqt/orm/expression/assignment.h>
#include <sqt/orm/querier/inserter/conflict_action.h>

namespace sqt {

template<ConflictAction CONFLICT_ACTION, typename ASSIGNMENT>
class EntityInserter {
public:
    static constexpr std::size_t ParameterIndex = 0;
    static constexpr std::size_t ParameterCount = 0;

    static std::string_view BuildSQL() {
        static const std::string sql = []() {
            "insert or {} into {} ({}) values ({})";
        };
        return sql;
    }

    static constexpr auto BuildPlaceholderBinders() {

    }

public:
    constexpr EntityInserter(ASSIGNMENT assignment) : assignment_(std::move(assignment)) {

    }

    void BindInlineParameters(Statement& statement) const {

    }

private:
    ASSIGNMENT assignment_;
};

}