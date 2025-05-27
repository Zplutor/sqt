#pragma once

/**
@file
    Defines the `sqt::Deleter<>` class template.
*/

#include <format>
#include <string_view>
#include <sqt/foundation/statement.h>
#include <sqt/orm/querier/where_capability.h>
#include <sqt/orm/table_mapping.h>
#include <sqt/orm/value/entity/entity_value_type.h>

namespace sqt {

/**
A primary deleter that deletes entities from the table.

@tparam ENTITY
    The entity type that the deleter deletes. It must satisfy the `sqt::EntityValueType` concept.

@details
    This primary deleter deletes entities from the table without any conditions.

    To create instances of this deleter, use the `sqt::DataContext::MakeDeleter()` method.

    This class template satisfies the `sqt::QuerierType` concept.

@see sqt::DataContext<>::MakeDeleter()
@see sqt::EntityValueType
@see sqt::QuerierType
*/
template<EntityValueType ENTITY>
class Deleter : public WhereCapability<Deleter<ENTITY>> {
public:
    static constexpr std::size_t ParameterIndex = 1;
    static constexpr std::size_t ParameterCount = 0;

    static std::string_view BuildSQL() {
        static const std::string sql = []() {
            return std::format("delete from {}", Table<ENTITY>.GetName());
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