#pragma once

#include <sqt/orm/expression/predicate_type.h>
#include <sqt/orm/querier/querier_type.h>

namespace sqt {

template<QuerierType QUERIER, PredicateType PREDICATE>
class WhereDecorator {
public:
    static constexpr std::size_t ParameterIndex =
        QUERIER::ParameterIndex + QUERIER::ParameterCount;

    static constexpr std::size_t ParameterCount = PREDICATE::ParameterCount;

    static std::string_view BuildSQL() {
        static const std::string sql = []() {
            return std::format("{} where {}", QUERIER::BuildSQL(), PREDICATE::BuildSQL());
        }();
        return sql;
    }

    static constexpr auto BuildPlaceholderBinders() {
        return std::tuple_cat(
            QUERIER::BuildPlaceholderBinders(),
            PREDICATE::BuildPlaceholderBinders(ParameterIndex));
    }

public:
    constexpr WhereDecorator(QUERIER QUERIER, PREDICATE predicate) :
        querier_(std::move(QUERIER)),
        predicate_(std::move(predicate)) {

    }

    void BindInlineParameters(Statement& statement) const {
        querier_.BindInlineParameters(statement);
        predicate_.BindInlineParameters(statement, ParameterIndex);
    }

private:
    QUERIER querier_;
    PREDICATE predicate_;
};

}