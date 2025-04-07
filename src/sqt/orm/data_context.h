#pragma once

/**
@file
    Defines the `sqt::DataContext<>` class template.
*/

#include <mutex>
#include <optional>
#include <vector>
#include <sqt/foundation/database.h>
#include <sqt/orm/executor/executor.h>
#include <sqt/orm/expression/operand/placeholder_operand.h>
#include <sqt/orm/querier/deleter/deleter.h>
#include <sqt/orm/querier/inserter/entity_inserter.h>
#include <sqt/orm/querier/selecter/column_selecter.h>
#include <sqt/orm/querier/selecter/entity_selecter.h>
#include <sqt/orm/querier/updater/column_updater.h>
#include <sqt/orm/querier/updater/entity_updater.h>
#include <sqt/orm/table/abstract_table.h>
#include <sqt/orm/internal/table_initializer.h>
#include <sqt/orm/value/entity/entire_entity_value_traits.h>
#include <sqt/orm/value/entity/entity_value_type.h>
#include <sqt/orm/value/entity/no_primary_key_entity_value_traits.h>

namespace sqt {

/**
Provides a set of operations for performing CRUD (Create, Read, Update, Delete) operations on a
database table corresponding to a specified entity type.

@tparam ENTITY
    The entity type that can be mapped to a database table. A table type for the entity must be 
    defined using the `SQT_TABLE_BEGIN` macro, and this table type must be registered using the 
    `SQT_REGISTER` macro.
    
@details
    One data context instance corresponds to a single table in a database. Multiple data context 
    instances can share the same database instance. The following code demonstrates how to create a
    data context instance:

    @code
    // The entity type, assuming its table type has been defined and registered.
    struct MyEntity { };

    // Open the database.
    auto db = sqt::Database::Open("MyDatabase.db");
    // Make the database shared.
    auto shared_db = std::make_shared<sqt::Database>(std::move(db));

    // Create the data context with the shared database.
    sqt::DataContext<MyEntity> data_context{ shared_db };
    @endcode

    The database table will be automatically initialized when the first CRUD operation is executed.
    Alternatively, the table can be initialized explicitly using the `InitializeTable()` method. 
    The table will be created if it does not exist, or altered only if:
    - new columns are added to the table;
    - new indexes are added to the table.

    @note
    Only column and index additions are supported. Any other structural changes to the table 
    (e.g., modifying or removing columns) are unsupported and will cause undefined behavior.

    `sqt::DataContext<>` provides two styles of interfaces for interacting with the database table:

    - Easy style

      Methods like `Insert()`, `Update()`, `Delete()`, and `Select()` provide simple, direct 
      interfaces for performing the corresponding operations. These methods are easy to use but not
      flexible enough for more complex scenarios.

      For example, `Select()` retrieves all columns of the table based on the primary key value, 
      without the option to select a subset of columns or apply custom conditions.

    - Complex style

      Complex interfaces are provided via static methods prefixed with `Make`, which create 
      queriers for the corresponding operations. Querier objects allow you to build SQL statements 
      and bind parameters, providing greater flexibility for complex queries.

      For example, the `MakeSelecter()` method creates a querier that can be used to select 
      specific columns and add conditions using the `Where()` method. Queriers also support 
      parameter binding, which improves performance by allowing the same query to be reused with 
      different parameters.

      To execute a querier, pass it to the `Prepare()` method, which returns an executor. The
      executor can be used to execute the SQL statement and retrieve the results.

@see SQT_TABLE_BEGIN
@see SQT_REGISTER
*/
template<EntityValueType ENTITY>
class DataContext {
public:
    template<ConflictAction CONFLICT_ACTION = ConflictAction::Abort>
    static constexpr auto MakeInserter() noexcept {
        using ValueTraits = EntireEntityValueTraits<ENTITY>;
        using Operand = PlaceholderOperand<ValueTraits>;
        return EntityInserter<CONFLICT_ACTION, Operand>{ Operand{} };
    }

    static constexpr auto MakeReplacer() noexcept {
        return MakeInserter<ConflictAction::Replace>();
    }

    template<ConflictAction CONFLICT_ACTION = ConflictAction::Abort>
    static constexpr auto MakeAutoIncInserter() noexcept requires AutoIncEntityValueType<ENTITY> {
        using ValueTraits = NoPrimaryKeyEntityValueTraits<ENTITY>;
        using Operand = PlaceholderOperand<ValueTraits>;
        return EntityInserter<CONFLICT_ACTION, Operand>{ Operand{} };
    }

    static constexpr auto MakeAutoIncReplacer() noexcept requires AutoIncEntityValueType<ENTITY> {
        return MakeAutoIncInserter<ConflictAction::Replace>();
    }

    static constexpr auto MakeUpdater() noexcept {
        using ValueTraits = EntireEntityValueTraits<ENTITY>;
        using Operand = PlaceholderOperand<ValueTraits>;
        return EntityUpdater<Operand>{ Operand{} };
    }

    static constexpr auto MakeNoPrimaryKeyUpdater() noexcept
        requires PrimaryKeyEntityValueType<ENTITY> {

        using ValueTraits = NoPrimaryKeyEntityValueTraits<ENTITY>;
        using Operand = PlaceholderOperand<ValueTraits>;
        return EntityUpdater<Operand>{ Operand{} };
    }

    template<AssignmentType... ASSIGNMENT>
    static constexpr auto MakeUpdater(ASSIGNMENT... assignments) noexcept {
        return ColumnUpdater<ASSIGNMENT...>{ std::move(assignments)... };
    }

    static constexpr auto MakeDeleter() noexcept {
        return Deleter<ENTITY>{};
    }

    static constexpr auto MakeSelecter() noexcept {
        return EntitySelecter<ENTITY>{};
    }

    template<ColumnType... COLUMN>
    static constexpr auto MakeSelecter(const COLUMN&... columns) noexcept {
        return ColumnSelecter<COLUMN...>{};
    }

public:
    /**
    Constructs an instance using the specified shared database.

    @param database
        The shared database instance to be used by the constructed instance. 

    @details
        The associated database table is not initialized (i.e., created or altered) during 
        construction. It will be automatically initialized when the first CRUD operation is 
        executed.

        To initialize the table explicitly before performing any operations, call the 
        `InitializeTable()` method.

    @see sqt::DataContext<>::InitializeTable()
    */
    explicit DataContext(std::shared_ptr<sqt::Database> database) noexcept :
        init_once_guard_(std::move(database)) {

    }

    DataContext(const DataContext&) = delete;
    DataContext& operator=(const DataContext&) = delete;

    template<QuerierType QUERIER>
    Executor<QUERIER> Prepare(const QUERIER& querier) {
        auto db = init_once_guard_.DB();
        auto sql = querier.BuildSQL();
        auto statement = db->PrepareStatement(sql);
        querier.BindInlineParameters(statement);
        return Executor{ querier, std::move(db), std::move(statement) };
    }

    /**
    Inserts the specified entity into the database table.

    @param entity
        The entity to be inserted.

    @return
        The generated row ID of the inserted entity.

    @throw sqt::SQLError
        Thrown if the insertion fails.

    @details
        This method inserts the entire entity into the database table, including the primary key.
        However, the primary key value is not automatically generated even if it is 
        auto-incremented. To automatically generate the primary key value, use `AutoIncInsert()`
        instead.

        If a unique constraint violation occurs, the insertion will fail and throw an exception. To
        avoid this, use `Replace()` or `AutoIncReplace()` to replace the existing row.

        For more control over the inserted columns or the conflict action, use the more flexible 
        `MakeInserter()` method from the complex style interface.

    @see sqt::DataContext<>::AutoIncInsert()
    @see sqt::DataContext<>::Replace()
    @see sqt::DataContext<>::AutoIncReplace()
    @see sqt::DataContext<>::MakeInserter()
    */
    std::int64_t Insert(const ENTITY& entity) {
        constexpr auto inserter = MakeInserter();
        return ExecuteEntityInserter(inserter, entity);
    }

    /**
    Inserts the specified entity into the database table, automatically generating the primary key
    value.

    @param entity
        The entity to be inserted.

    @return
        The generated row ID of the inserted entity.

    @throw sqt::SQLError
        Thrown if the insertion fails.

    @details
        This method is similar to the `Insert()` method, expect that the primary key value in the 
        entity is ignored and automatically generated.

        To avoid unique constraint violations due to unique indexes, use the `AutoIncReplace()` 
        method to replace the existing row instead.

        @note
        This method is only available if the entity type has an auto-incremented primary key. Use 
        the `SQT_PRIMARY_KEY_AUTO_INC` macro to define an auto-incremented primary key.

    @see sqt::DataContext<>::Insert()
    @see sqt::DataContext<>::AutoIncReplace()
    @see SQT_PRIMARY_KEY_AUTO_INC
    */
    std::int64_t AutoIncInsert(const ENTITY& entity) requires AutoIncEntityValueType<ENTITY> {
        constexpr auto inserter = MakeAutoIncInserter();
        return ExecuteEntityInserter(inserter, entity);
    }

    /**
    Inserts the specified entity into the database table, replacing the existing row.

    @param entity
        The entity to be inserted.

    @return
        The generated row ID of the inserted entity.

    @throw sqt::SQLError
        Thrown if the insertion fails.

    @details
        This method is similar to the `Insert()` method, except that it replaces the existing row 
        if a unique constraint violation occurs.

        To automatically generate the primary key value, use `AutoIncReplace()` method instead.

        For more control over the inserted columns, use the more flexible `MakeReplacer()` method 
        from the complex style interface.

    @see sqt::DataContext<>::Insert()
    @see sqt::DataContext<>::AutoIncReplace()
    @see sqt::DataContext<>::MakeReplacer()
    */
    std::int64_t Replace(const ENTITY& entity) {
        constexpr auto replacer = MakeReplacer();
        return ExecuteEntityInserter(replacer, entity);
    }

    std::int64_t AutoIncReplace(const ENTITY& entity) {
        constexpr auto replacer = MakeAutoIncReplacer();
        return ExecuteEntityInserter(replacer, entity);
    }

    template<typename E = ENTITY>
    bool Update(const E& entity) requires PrimaryKeyEntityValueType<E> {
        constexpr auto updater = MakeNoPrimaryKeyUpdater().Where(Table<E>.PrimaryKey == sqt::_);
        auto executor = Prepare(updater);
        executor.BeginBind().Bind(entity).BindFromEntity(entity);
        executor.Execute();
        return executor.LastChanges() > 0;
    }

    std::size_t DeleteAll() {
        constexpr auto deleter = MakeDeleter();
        auto executor = Prepare(deleter);
        executor.Execute();
        return executor.LastChanges();
    }

    template<typename E = ENTITY>
    bool Delete(const typename TableType<E>::PrimaryKeyType::ValueType& primary_key) 
        requires PrimaryKeyEntityValueType<E> {

        constexpr auto deleter = MakeDeleter().Where(Table<E>.PrimaryKey == sqt::_);
        auto executor = Prepare(deleter);
        executor.BeginBind().Bind(primary_key);
        executor.Execute();
        return executor.LastChanges() > 0;
    }

    std::vector<ENTITY> SelectAll() {
        constexpr auto selecter = MakeSelecter();
        auto executor = Prepare(selecter);
        auto result = executor.Execute();
        return std::vector<ENTITY>{ result.begin(), result.end() };
    }

    template<typename E = ENTITY>
    std::optional<E> Select(const typename TableType<E>::PrimaryKeyType::ValueType& primary_key) 
        requires PrimaryKeyEntityValueType<E> {

        constexpr auto selecter = MakeSelecter().Where(Table<E>.PrimaryKey == sqt::_);
        auto executor = Prepare(selecter);
        executor.BeginBind().Bind(primary_key);
        auto result = executor.Execute();
        auto begin = result.begin();
        if (begin != result.end()) {
            return *begin;
        }
        return std::nullopt;
    }

    /**
    Explicitly initializes the database table associated with this data context.

    @throw sqt::SQLError
        Thrown if the table initialization fails.

    @details
        This method is typically not required, as the table will be automatically initialized upon 
        the first CRUD operation. However, it can be useful in scenarios where the table must be 
        prepared before any operations are performed.

        Calling this method multiple times is safe; only the first call takes effect.
    */
    void InitializeTable() {
        init_once_guard_.DB();
    }

    /**
    Gets the shared database instance used by this data context.

    @return
        The shared database instance.
    */
    const std::shared_ptr<sqt::Database>& Database() const noexcept {
        return init_once_guard_.DB();
    }

private:
    template<typename INSERTER>
    std::int64_t ExecuteEntityInserter(const INSERTER& inserter, const ENTITY& entity) {
        auto executor = Prepare(inserter);
        executor.BeginBind().Bind(entity);
        executor.Execute();
        return executor.LastInsertRowID();
    }

private:
    class InitOnceGuard {
    public:
        InitOnceGuard(std::shared_ptr<sqt::Database> db) noexcept : db_(std::move(db)) {

        }

        InitOnceGuard(const InitOnceGuard&) = delete;
        InitOnceGuard& operator=(const InitOnceGuard&) = delete;

        const std::shared_ptr<sqt::Database>& DB() const {
            return db_;
        }

        const std::shared_ptr<sqt::Database>& DB() {
            std::call_once(init_once_flag_, [this]() {
                internal::TableInitializer::Initialize(Table<ENTITY>, *db_);
            });
            return db_;
        }

    private:
        std::shared_ptr<sqt::Database> db_;
        std::once_flag init_once_flag_;
    };

private:
    InitOnceGuard init_once_guard_;
};

}
