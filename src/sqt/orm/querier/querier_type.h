#pragma once

/**
@file
    Defines the `sqt::QuerierType` concept.
*/

#include <concepts>
#include <sqt/foundation/statement.h>
#include <sqt/orm/expression/binder/binder_chain.h>
#include <sqt/orm/expression/binder/binder_tuple_type.h>

namespace sqt {

/**
Constraints a type to be a querier type, which corresponds to a SQL statement that can be executed.

@details
    @b Requirements
    - The type must have a static constant `ParameterIndex` of type `std::size_t`, with a value 
      greater than 0.
    - The type must have a static constant `ParameterCount` of type `std::size_t`.
    - The type must have a static method `BuildSQL()` with the following signature:
      @code{.cpp}
      static std::string_view BuildSQL();
      @endcode
    - The type must have a static method `BuildPlaceholderBinders()` with the following signature:
      @code{.cpp}
      static auto BuildPlaceholderBinders() noexcept;
      @endcode
      The return type must satisfy the `sqt::BinderTupleType` concept.
    - The type must have a member function `BindInlineParameters()` with the following signature:
      @code{.cpp}
      void BindInlineParameters(sqt::Statement& statement) const;
      @endcode

    A querier is an encapsulation for a SQL statement. Each querier instance corresponds to a 
    well-formed SQL statement that can be executed. There are four types of queriers:
    - Inserter, which corresponds to an `INSERT` SQL statement.
    - Updater, which corresponds to an `UPDATE` SQL statement.
    - Deleter, which corresponds to a `DELETE` SQL statement.
    - Selecter, which corresponds to a `SELECT` SQL statement, constrained by the 
      `sqt::SelecterType` concept.

    The `Make*()` methods in `sqt::DataContext<>` are used to create queriers, referred to as 
    primary queriers, which contain the core components of a SQL statement. For instance:
    @code{.cpp}
    // The entity type, assuming its table type has been defined and registered, and its columns' 
    // names are defined as the same as the entity's field names:
    struct MyEntity {
        int id{};
        std::string name;
    };

    //Create a primary selecter that selects all entities.
    constexpr auto selecter = sqt::DataContext<MyEntity>::MakeSelecter();
    @endcode

    The above code creates a primary selecter corresponds to the following SQL statement:
    @code{.sql}
    SELECT id, name FROM MyEntity;
    @endcode

    Decorated queriers add additional clauses to the SQL statement. They are created by decorative 
    methods of queriers (either primary queriers or decorated queriers). For instance:
    @code{.cpp}
    constexpr auto selecter = sqt::DataContext<MyEntity>::MakeSelecter()
        .Where(sqt::Table<MyEntity>.name != "Unknown")
        .OrderBy(sqt::Table<MyEntity>.id.Desc());
    @endcode

    The above code creates a decorated selecter in chain fashin. The selecter corresponds to 
    the following SQL statement:
    @code{.sql}
    SELECT id, name FROM MyEntity WHERE name <> "Unknown" ORDER BY id DESC;
    @endcode

@see sqt::BinderTupleType
@see sqt::DataContext<>
@see sqt::SelecterType
*/
template<typename T>
concept QuerierType = 
    requires {
        { T::ParameterIndex } -> std::same_as<const std::size_t&>;
        requires T::ParameterIndex > 0;
        { T::ParameterCount } -> std::same_as<const std::size_t&>;
        { T::BuildSQL() } -> std::same_as<std::string_view>;
        { T::BuildPlaceholderBinders() } noexcept -> BinderTupleType;
    } 
    &&
    requires(const T t, Statement& statement) {
        { t.BindInlineParameters(statement) } -> std::same_as<void>;
    };

}