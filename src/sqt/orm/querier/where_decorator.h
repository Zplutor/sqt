#pragma once

/**
@file
    Defines the `sqt::WhereDecorator<>` class template.
*/

#include <sqt/orm/expression/predicate_type.h>
#include <sqt/orm/querier/querier_type.h>

namespace sqt {

/**
A querier decorator that adds a `WHERE` clause to the SQL statement of the decorated querier.

@tparam QUERIER
    The querier type to be decorated, which must satisfy the `sqt::QuerierType` concept.

@tparam PREDICATE
    The predicate type to be applied in the `WHERE` clause. It must satisfy the 
    `sqt::PredicateType` concept.

@details
    To create instances of this class template, use the `Where()` method of the 
    `sqt::WhereCapability<>` class template, which is a mixin for queriers that support the 
    `WHERE` clause.

    This class template satisfies the `sqt::QuerierType` concept.

@see sqt::PredicateType
@see sqt::QuerierType
@see sqt::WhereCapability<>
*/
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

    static constexpr auto BuildPlaceholderBinders() noexcept {
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