#pragma once

/**
@file
    Defines the `sqt::BaseSelecter<>` class template.
*/

#include <format>
#include <string>
#include <string_view>
#include <sqt/orm/querier/selecter/limit_select_capability.h>
#include <sqt/orm/querier/selecter/order_by_select_capability.h>
#include <sqt/orm/querier/selecter/where_select_decorator.h>
#include <sqt/orm/querier/where_capability.h>
#include <sqt/orm/table_mapping.h>

namespace sqt {

/**
The base class template for primary selecters.

@tparam SELECTER
    The type of the primary selecter that derives from this class template.

@details
    This class template defines the common functionalities for primary selecters.

    There are two primary selecters provided by the framework:
    - `sqt::EntitySelecter<>`, which selects the entire entity from the table.
    - `sqt::ColumnSelecter<>`, which selects specific columns from the table.

@see sqt::ColumnSelecter<>
@see sqt::EntitySelecter<>
*/
template<typename SELECTER>
class BaseSelecter : 
    public WhereCapability<SELECTER, WhereSelectDecorator>,
    public OrderBySelectCapability<SELECTER>,
    public LimitSelectCapability<SELECTER> {

public:
    static constexpr std::size_t ParameterIndex = 1;
    static constexpr std::size_t ParameterCount = 0;

    /**
    Creates a string view of the `SELECT` SQL statement.

    @return
        A string view of the `SELECT` SQL statement without any clause.
    */
    static std::string_view BuildSQL() {

        static const std::string sql = std::format(
            "select {} from {}",
            SELECTER::BuildColumnNames(),
            Table<SELECTER::EntityType>.GetName());

        return sql;
    }

    /**
    Creates a tuple of binders for placeholders.

    @return
        An empty tuple.

    @details
        Primary selecters do not have placeholders, so the binders are empty.
    */
    static constexpr auto BuildPlaceholderBinders() noexcept {
        return std::tuple<>{};
    }

public:
    /**
    Binds inline parameters to the statement.

    @details
        Primary selecters do not have inline parameters, so this method does nothing.
    */
    constexpr void BindInlineParameters(Statement&) const noexcept {

    }
};

}