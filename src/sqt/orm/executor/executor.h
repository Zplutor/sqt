#pragma once

/**
@file
    Defines the `sqt::Executor<>` class template.
*/

#include <sqt/foundation/statement.h>
#include <sqt/orm/executor/result.h>
#include <sqt/orm/expression/binder/binder_chain.h>
#include <sqt/orm/querier/bindable_querier_type.h>
#include <sqt/orm/querier/querier_type.h>

namespace sqt {

/**
Executes the statement of a querier and retrieves the results.

@tparam QUERIER
    The type of the querier to be executed. The available interfaces provided by the executor 
    depend on the querier type.

@details
    To create an executor, use the `sqt::DataContext::Prepare()` method, passing the querier as 
    an argument. The executor shares the same database instance as the data context, so it is safe
    to use the executor even after the data context is destructed.

    If the querier contains placeholders, call the `BeginBindings()` method to begin a binding 
    process that binds parameters to the placeholders.

    The `Execute()` method is used to execute the statement. For non-select queriers, this method 
    returns nothing, but callers can use the `LastChanges()` method to retrieve the number of rows 
    affected by the query, or use the `LastInsertRowID()` method to retrieve the row ID of the 
    last inserted row. 
    
    For select queriers, the `Execute()` method returns a `sqt::Result<QUERIER>` instance, which
    can be used to retrieve the results of the query. Refer to `sqt::DataContext::MakeSelecter()`
    for the example of retrieving results.

    An executor can be reused by calling the `Reset()` method, which resets the statement's state
    to allow for re-execution. This is useful when the same statement needs to be executed multiple
    times with different parameters.

@see sqt::DataContext<>::Prepare()
@see sqt::QuerierType
@see sqt::Result<>
*/
template<QuerierType QUERIER>
class Executor {
public:
    /**
    Constructs an executor instance.

    @param statement
        A prepared statement of the querier.

    @param database
        The database instance associated with the executor.

    @details
        This method is called internally by the `sqt::DataContext<>::Prepare()` method to create an 
        executor. It is not intended to be called directly by users.
        
    @see sqt::DataContext<>::Prepare() 
    */
    Executor(Statement statement, std::shared_ptr<Database> database) noexcept :
        statement_(std::move(statement)),
        database_(std::move(database)) {

    }

    Executor(const Executor&) = delete;
    Executor& operator=(const Executor&) = delete;

    Executor(Executor&&) noexcept = default;
    Executor& operator=(Executor&&) noexcept = default;

    /**
    Begins a binding process to bind parameters to the placeholders.

    @return
        A `sqt::BinderChain<>` instance corresponds to the placeholders in the querier. The 
        instance remains valid until the executor is destructed.

    @details
        @note
        This method is only available for queriers that contain placeholders.

        The returned `sqt::BinderChain<>` instance enables binding parameters in a chain fashion. 
        The number of binders, their order, and their value types correspond exactly to the 
        placeholders in the querier. The following code demonstrates how to use the 
        `BeginBindings()` method:

        @code{.cpp}
        // The entity type, assuming its table type has been defined and registered, and its
        // columns' names are defined as the same as the entity's field names.
        struct MyEntity {
            int id{};
            std::string name;
            int age{};
        };

        // Create an inserter with three placeholders.
        constexpr auto inserter = sqt::DataContext<MyEntity>::MakeInserter(
            sqt::Table<MyEntity>.id = sqt::_,
            sqt::Table<MyEntity>.name = sqt::_,
            sqt::Table<MyEntity>.age = sqt::_
        );

        // Create an executor for the inserter.
        sqt::DataContext<MyEntity> data_context{ shared_db };
        auto executor = data_context.Prepare(inserter);

        // Bind parameters to the placeholders.
        executor.BeginBindings()
            .Bind(1)            // Binds to the first placeholder of the id column.
            .Bind("The First")  // Binds to the second placeholder of the name column.
            .Bind(18);          // Binds to the third placeholder of the age column.

        // Execute the statement.
        executor.Execute();
        @endcode

    @see sqt::BinderChain<>
    */
    auto BeginBindings() noexcept requires BindableQuerierType<QUERIER> {
        constexpr auto binders = QUERIER::BuildPlaceholderBinders();
        return MakeBinderChain(statement_, binders);
    }

    /**
    Executes the statement for the non-select querier.

    @throw sqt::SQLError
        Thrown if the execution fails.

    @details
        @note
        This method is available only if the querier does not satisfy the `sqt::SelecterType` 
        concept.

        This method executes a non-select statement, such as an `INSERT`, `UPDATE`, or `DELETE` 
        statement. The following methods can be used to retrieve the results of the execution:
        - `LastChanges()` for retrieving the number of rows affected by the statement.
        - `LastInsertRowID()` for retrieving the row ID of the last inserted row.

        To re-execute the same statement, call the `Reset()` method first and then call this method
        again.

    @see sqt::Executor<>::LastChanges()
    @see sqt::Executor<>::LastInsertRowID()
    @see sqt::Executor<>::Reset()
    @see sqt::SelecterType
    */
    void Execute() requires !SelecterType<QUERIER> {
        statement_.Step();
    }

    /**
    Creates a `sqt::Result<>` instance that can be used to retrieve the results of the select 
    querier.

    @return
        A `sqt::Result<>` instance. The instance remains valid until the executor is destructed or
        the `Reset()` method is called.

    @details
        @note
        This method is available only if the querier satisfies the `sqt::SelecterType` concept.

        This method does not immediately execute the statement. Instead, it creates a 
        `sqt::Result<>` instance, and the execution will be deferred until the first retrieval from 
        the returned instance.

        @warning
        This method should be called only once for each execution. To retrieve the results again, 
        call the `Reset()` method first to reset the statement's state, and then call this method
        again to create a new `sqt::Result<>` instance.
    
    @see sqt::Executor<>::Reset()
    @see sqt::Result<>
    @see sqt::SelecterType
    */
    [[nodiscard]]
    auto Execute() noexcept requires SelecterType<QUERIER> {
        return sqt::Result<QUERIER>{ statement_ };
    }

    /**
    Retrieves the number of rows affected by the last executed non-select statement.

    @return
        The number of rows affected by the statement.

    @details
        @note
        This method is available only if the querier does not satisfy the `sqt::SelecterType` 
        concept.
    */
    std::size_t LastChanges() const noexcept requires !SelecterType<QUERIER> {
        return database_->LastChanges();
    }

    /**
    Retrieves the row ID of the last inserted row.

    @return
        The last inserted row ID.

    @details
        @note
        This method is available only if the querier does not satisfy the `sqt::SelecterType`
        concept.
    */
    std::int64_t LastInsertRowID() const noexcept requires !SelecterType<QUERIER> {
        return database_->LastInsertRowID();
    }
    
    /**
    Resets the statement's state for reusing.

    @throw sqt::SQLError
        Thrown if the reset fails.

    @details
        This method resets the statement's internal state, allowing the query to be re-executed.
        
        The placeholder bindings are not cleared, so they remain intact for reuse. To modify the 
        bindings, call the `BeginBindings()` method again and bind new parameters before calling 
        the `Execute()` method.

    @see sqt::Executor<>::BeginBindings()
    @see sqt::Executor<>::Execute()
    */
    void Reset() {
        statement_.Reset();
    }

private:
    Statement statement_;
    std::shared_ptr<Database> database_;
};

}