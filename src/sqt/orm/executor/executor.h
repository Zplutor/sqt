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

    void Execute() requires !SelecterType<QUERIER> {
        statement_.Step();
    }

    std::size_t LastChanges() const requires !SelecterType<QUERIER> {
        return database_->LastChanges();
    }

    std::int64_t LastInsertRowID() const requires !SelecterType<QUERIER> {
        return database_->LastInsertRowID();
    }
    
    [[nodiscard]]
    auto Execute() requires SelecterType<QUERIER> {
        return sqt::Result<QUERIER>{ statement_ };
    }

    void Reset() {
        statement_.Reset();
    }

private:
    Statement statement_;
    std::shared_ptr<Database> database_;
};

}