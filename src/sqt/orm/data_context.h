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
#include <sqt/orm/querier/inserter/column_inserter.h>
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

    @code{.cpp}
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

    @warning
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

@see SQT_REGISTER
@see SQT_TABLE_BEGIN

*/
template<EntityValueType ENTITY>
class DataContext {
public:
    /**
    Creates an inserter for inserting an entire entity into the database table.

    @tparam CONFLICT_ACTION
        The conflict action to be used when a unique constraint violation occurs. The default
        action is `sqt::ConflictAction::Abort`.

    @return
        A new inserter instance.

    @details
        The returned inserter corresponds to an `INSERT` SQL statement that inserts all columns 
        of the entity into the database table. The following alternatives provide more control over
        the inserted columns:

        - `MakeAutoIncInserter()` for inserting non-primary key columns while auto-generating the
          primary key.
        - `MakeInserter(ASSIGNMENTS&&...)` for inserting specific columns.

        The `MakeReplacer()` method is a shorthand for 
        `MakeInserter<sqt::ConflictAction::Replace>()`.

        A placeholder for the entity is implicitly added to the returned inserter. To execute the 
        inserter, an entity instance must be bound. The following code demonstrates how to use the 
        inserter:
        
        @code{.cpp}
        // The entity type, assuming its table type has been defined and registered.
        struct MyEntity {
            int id{};
            std::string name;
        };

        // Create the inserter.
        constexpr auto inserter = sqt::DataContext<MyEntity>::MakeInserter();

        // Create a data context, assuming the shared_db is an opened database instance.
        sqt::DataContext<MyEntity> data_context{ shared_db };

        // Prepare the inserter to create a corresponding executor.
        auto executor = data_context.Prepare(inserter);

        // Bind an entity to the executor.
        MyEntity entity{ 1, "The First" };
        executor.BeginBind().Bind(entity);

        // Execute the statement.
        executor.Execute();
        @endcode

        For an easier-to-use method, use the `Insert()` method from the easy style interface.
    
    @see sqt::DataContext<>::Insert()
    @see sqt::DataContext<>::MakeAutoIncInserter()
    @see sqt::DataContext<>::MakeInserter(ASSIGNMENTS&&... assignments)
    @see sqt::DataContext<>::MakeReplacer()
    */
    template<ConflictAction CONFLICT_ACTION = ConflictAction::Abort>
    static constexpr auto MakeInserter() noexcept {
        using ValueTraits = EntireEntityValueTraits<ENTITY>;
        using Operand = PlaceholderOperand<ValueTraits>;
        return EntityInserter<CONFLICT_ACTION, Operand>{ Operand{} };
    }

    /**
    Creates an inserter for inserting the specified columns of the entity into the database table.

    @tparam CONFLICT_ACTION
        The conflict action to be used when a unique constraint violation occurs. The default
        action is `sqt::ConflictAction::Abort`.

    @tparam ASSIGNMENTS
        A pack of the assignment types.

    @param assignments
        The assignments specifying the columns and their values to be inserted.

    @return
        A new inserter instance.

    @details
        This method provides more control over the inserted columns compared to the 
        `MakeInserter()` method. It allows specifying which columns to insert and their 
        corresponding values.

        The `MakeReplacer(ASSIGNMENTS&&...)` method is a shorthand for 
        `MakeInserter<sqt::ConflictAction::Replace>(assignments)`.

        For more information about the assignments, refer to the `sqt::AssignmentType` concept.

    @see sqt::AssignmentType
    @see sqt::DataContext<>::MakeInserter()
    @see sqt::DataContext<>::MakeReplacer(ASSIGNMENTS&&... assignments);
    */
    template<ConflictAction CONFLICT_ACTION = ConflictAction::Abort, AssignmentType... ASSIGNMENTS>
    static constexpr auto MakeInserter(ASSIGNMENTS&&... assignments) noexcept {
        return ColumnInserter<CONFLICT_ACTION, ASSIGNMENTS...>{
            std::forward<ASSIGNMENTS>(assignments)...
        };
    }

    /**
    Creates an inserter for inserting an entire entity into the database table, replacing the 
    existing row.

    @return
        A new inserter instance.

    @details
        This method is a shorthand for `MakeInserter<sqt::ConflictAction::Replace>()`.

    @see sqt::DataContext<>::MakeInserter()
    */
    static constexpr auto MakeReplacer() noexcept {
        return MakeInserter<ConflictAction::Replace>();
    }

    /**
    Creates an inserter for inserting the specified columns of the entity into the database table,
    replacing the existing row.

    @tparam ASSIGNMENTS
        A pack of the assignment types.

    @param assignments
        The assignments specifying the columns and their values to be inserted.

    @return
        The new inserter instance.

    @details
        This method is a shorthand for `MakeInserter<sqt::ConflictAction::Replace>(assignments)`.

    @see sqt::AssignmentType
    @see sqt::DataContext<>::MakeInserter(ASSIGNMENTS&&... assignments)
    */
    template<AssignmentType... ASSIGNMENTS>
    static constexpr auto MakeReplacer(ASSIGNMENTS&&... assignments) noexcept {
        return MakeInserter<ConflictAction::Replace>(std::forward<ASSIGNMENTS>(assignments)...);
    }

    /**
    Creates an inserter for inserting an entity into the database table, automatically generating 
    the primary key value.

    @tparam CONFLICT_ACTION
        The conflict action to be used when an unique constraint violation occurs. The default
        action is `sqt::ConflictAction::Abort`.

    @return
        A new inserter instance.

    @details
        This method is similar to the `MakeInserter()` method, except that the primary key column
        is not inserted and its value is automatically generated.

        The `MakeAutoIncReplacer()` method is a shorthand for 
        `MakeAutoIncInserter<sqt::ConflictAction::Replace>()`.

        @note
        This method is only available if the entity type has an auto-incremented primary key. Use
        the `SQT_PRIMARY_KEY_AUTO_INC` macro to define an auto-incremented primary key.

        For an easier-to-use method, use the `AutoIncInsert()` method from the easy style
        interface.

    @see sqt::DataContext<>::AutoIncInsert()
    @see sqt::DataContext<>::MakeAutoIncReplacer()
    @see SQT_PRIMARY_KEY_AUTO_INC
    */
    template<ConflictAction CONFLICT_ACTION = ConflictAction::Abort>
    static constexpr auto MakeAutoIncInserter() noexcept requires AutoIncEntityValueType<ENTITY> {
        using ValueTraits = NoPrimaryKeyEntityValueTraits<ENTITY>;
        using Operand = PlaceholderOperand<ValueTraits>;
        return EntityInserter<CONFLICT_ACTION, Operand>{ Operand{} };
    }

    /**
    Creates an inserter for inserting an entity into the database table, automatically generating
    the primary key value and replacing the existing row.

    @return
        A new inserter instance.

    @details
        This method is a shorthand for `MakeAutoIncInserter<sqt::ConflictAction::Replace>()`.

    @see sqt::DataContext<>::AutoIncReplace()
    @see sqt::DataContext<>::MakeAutoIncInserter()
    */
    static constexpr auto MakeAutoIncReplacer() noexcept requires AutoIncEntityValueType<ENTITY> {
        return MakeAutoIncInserter<ConflictAction::Replace>();
    }

    /**
    Creates an updater for updating all columns in the database table.

    @tparam CONFLICT_ACTION
        The conflict action to be used when an unique constraint violation occurs. The default
        action is `sqt::ConflictAction::Abort`.

    @return
        The new updater instance.

    @details
        The returned updater corresponds to an `UPDATE` SQL statement without any conditions, so it
        will update all rows in the database table. To control which rows to update, use the 
        `Where()` method of the updater to create a new updater with conditions. 

        A placeholder for the entity is implicitly added to the returned updater. To execute the
        updater, an entity instance must be bound. 
        
        The following code demonstrates how to use the updater:
        @code{.cpp}
        // The entity type, assuming its table type has been defined and registered, and its
        // columns' names are defined as the same as the entity's field names.
        struct MyEntity {
            int id{};
            std::string name;
        };

        // Create an updater with condition.
        constexpr auto updater = sqt::DataContext<MyEntity>::MakeUpdater().Where(
            sqt::Table<MyEntity>.id == 1
        );

        // Create a data context, assuming the shared_db is an opened database instance.
        sqt::DataContext<MyEntity> data_context{ shared_db };

        // Prepare the updater to create a corresponding executor.
        auto executor = data_context.Prepare(updater);

        // Bind an entity to the executor.
        MyEntity entity{ 1, "The First" };
        executor.BeginBind().Bind(entity);

        // Execute the statement.
        executor.Execute();
        @endcode

        The returned instance updates all columns of the entity type. The following alternatives
        provides more control over the updated columns:
        - `MakeNoPrimaryKeyUpdater()` for updating non-primary key columns. It is typically used 
          when updating the entity by its primary key value, reducing the unnecessary overhead of
          updating the primary key columns.
        - `MakeUpdater(ASSIGNMENTS&&...)` for updating specific columns.

    @see sqt::DataContext<>::MakeNoPrimaryKeyUpdater()
    @see sqt::DataContext<>::MakeUpdater(ASSIGNMENTS&&... assignments)
    */
    template<ConflictAction CONFLICT_ACTION = ConflictAction::Abort>
    static constexpr auto MakeUpdater() noexcept {
        using ValueTraits = EntireEntityValueTraits<ENTITY>;
        using Operand = PlaceholderOperand<ValueTraits>;
        return EntityUpdater<CONFLICT_ACTION, Operand>{ Operand{} };
    }

    /**
    Creates an updater for updating non-primary key columns in the database table.

    @tparam CONFLICT_ACTION
        The conflict action to be used when an unique constraint violation occurs. The default
        action is `sqt::ConflictAction::Abort`.

    @return
        A new updater instance.

    @details
        This method is similar to the `MakeUpdater()` method, except that it updates only the 
        non-primary key columns of the entity type. It is typically used when updating the
        entity by its primary key value, reducing the unnecessary overhead of updating the primary
        key columns.

        @note
        This method is only available if the entity type has a primary key. Use the 
        `SQT_PRIMARY_KEY` or `SQT_PRIMARY_KEY_AUTO_INC` macro to define a primary key.

    @see sqt::DataContext<>::MakeUpdater()
    @see sqt::DataContext<>::MakeUpdater(ASSIGNMENTS&&... assignments)
    @see SQT_PRIMARY_KEY
    @see SQT_PRIMARY_KEY_AUTO_INC
    */
    template<ConflictAction CONFLICT_ACTION = ConflictAction::Abort>
    static constexpr auto MakeNoPrimaryKeyUpdater() noexcept
        requires PrimaryKeyEntityValueType<ENTITY> {

        using ValueTraits = NoPrimaryKeyEntityValueTraits<ENTITY>;
        using Operand = PlaceholderOperand<ValueTraits>;
        return EntityUpdater<CONFLICT_ACTION, Operand>{ Operand{} };
    }

    /**
    Creates an updater for updating the spcified columns in the database table.

    @tparam CONFLICT_ACTION
        The conflict action to be used when an unique constraint violation occurs. The default
        action is `sqt::ConflictAction::Abort`.

    @tparam ASSIGNMENTS
        A pack of the assignment types.

    @param assignments
        The assignments specifying the columns and their values to be updated.

    @return
        A new updater instance.

    @details
        This method provides more control over the updated columns compared to the `MakeUpdater()` 
        method. It allows specifying which columns to update and their corresponding values.

        For more information about the assignments, refer to the `sqt::AssignmentType`.
    
    @see sqt::AssignmentType
    @see sqt::DataContext<>::MakeNoPrimaryKeyUpdater()
    @see sqt::DataContext<>::MakeUpdater()
    */
    template<ConflictAction CONFLICT_ACTION = ConflictAction::Abort, AssignmentType... ASSIGNMENTS>
    static constexpr auto MakeUpdater(ASSIGNMENTS&&... assignments) noexcept {
        return ColumnUpdater<CONFLICT_ACTION, ASSIGNMENTS...>{
            std::forward<ASSIGNMENTS>(assignments)...
        };
    }

    /**
    Creates a deleter for deleting rows from the database table.

    @return
        A new deleter instance.

    @details
        The returned deleter corresponds to a `DELETE` SQL statement without any conditions, so it
        will deleter all rows from the table. To control which rows to delete, use the `Where()` 
        method of the deleter to create a new deleter with conditions. The following code 
        demonstrates how to use the deleter:

        @code{.cpp}
        // The entity type, assuming its table type has been defined and registered, and its
        // columns' names are defined as the same as the entity's field names.
        struct MyEntity {
            int id{};
            std::string name;
        };

        // Create the deleter with a condition.
        constexpr auto deleter = sqt::DataContext<MyEntity>::MakeDeleter().Where(
            sqt::Table<MyEntity>.id == 1
        );

        // Create a data context, assuming the shared_db is an opened database instance.
        sqt::DataContext<MyEntity> data_context{ shared_db };

        // Prepare the deleter to create a corresponding executor.
        auto executor = data_context.Prepare(deleter);

        // Execute the statement.
        executor.Execute();
        @endcode

        For easier-to-use methods, use the following methods from the easy style interface:

        - `Delete()` for deleting a row by the specified primary key value.
        - `DeleteAll()` for deleting all rows in the table.

    @see sqt::DataContext<>::Delete()
    @see sqt::DataContext<>::DeleteAll()
    */
    static constexpr auto MakeDeleter() noexcept {
        return Deleter<ENTITY>{};
    }

    /**
    Creates a selecter for retrieveing entities from the database table.

    @return
        A new selecter instance, whose result element type is the entity type.

    @details
        The returned selecter corresponds to a `SELECT` SQL statement without any conditions, so it
        will select all entities from the table. To apply select conditions, use the `Where()`,
        `OrderBy()`, and `Limit()` methods of the selecter to create a new selecter with 
        conditions. The following code demonstrates how to use the selecter:

        @code{.cpp}
        // The entity type, assuming its table type has been defined and registered, and its
        // columns' names are defined as the same as the entity's field names.
        struct MyEntity {
            int id{};
            std::string name;
        };

        // Create the selecter with a condition.
        auto selecter = sqt::DataContext<MyEntity>::MakeSelecter().Where(
            sqt::Table<MyEntity>.name != "Unknown"
        );

        // Create a data context, assuming the shared_db is an opened database instance.
        sqt::DataContext<MyEntity> data_context{ shared_db };

        // Prepare the selecter to create a corresponding executor.
        auto executor = data_context.Prepare(selecter);

        // Execute the statement to obtain the result.
        auto result = executor.Execute();

        // Iterate through the result and print the entities.
        for (const auto& entity : result) {
            std::cout << "ID: " << entity.id << ", Name: " << entity.name << '\n';
        }
        @endcode

        The returned selecter selects all columns of the table. To control which columns to select, 
        use the `MakeSelecter(const COLUMN&&...)` method instead.

        For easier-to-use methods, use the following methods from the easy style interface:
        - `Select()` for selecting a single entity by the specified primary key value.
        - `SelectAll()` for selecting all entities in the table.

    @see sqt::DataContext<>::MakeSelecter(const COLUMNS&... columns);
    @see sqt::DataContext<>::Select()
    @see sqt::DataContext<>::SelectAll()
    */
    static constexpr auto MakeSelecter() noexcept {
        return EntitySelecter<ENTITY>{};
    }

    /**
    Creates a selecter for retrieveing the specified columns from the database table.

    @tparam COLUMNS
        A pack of the column types.

    @param columns
        The columns to be retrieved.

    @return
        A new selecter instance, whose result element type is a composite value type (a 
        `std::tuple<>` of the specified columns' value types).

    @details
        This method is similar to the `MakeSelecter()` method, with the following differences:
        - The returned selecter selects only the specified columns of the table, rather than all 
          columns.
        - The result element type is a composite value type rather than the entity type.

        The following code demonstrates how to use the selecter:

        @code{.cpp}
        // The entity type, assuming its table type has been defined and registered, and its
        // columns' names are defined as the same as the entity's field names.
        struct MyEntity {
            int id{};
            std::string name;
        };

        // Create the selecter with two columns.
        auto selecter = sqt::DataContext<MyEntity>::MakeSelecter(
            sqt::Table<MyEntity>.id,
            sqt::Table<MyEntity>.name,
        );

        // Create a data context, assuming the shared_db is an opened database instance.
        sqt::DataContext<MyEntity> data_context{ shared_db };

        // Prepare the selecter to create a corresponding executor.
        auto executor = data_context.Prepare(selecter);

        // Execute the statement to obtain the result.
        auto result = executor.Execute();

        // Iterate through the result and print the tuples.
        for (const auto& tuple : result) {
            std::cout << "ID: " << std::get<0>(tuple) << ", Name: " << std::get<1>(tuple) << '\n';
        }
        @endcode
        
    @see sqt::DataContext<>::MakeSelecter()
    @see sqt::DataContext<>::Select()
    @see sqt::DataContext<>::SelectAll()
    */
    template<ColumnType... COLUMNS>
    static constexpr auto MakeSelecter(const COLUMNS&... columns) noexcept {
        return ColumnSelecter<COLUMNS...>{};
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

    /**
    Creates an executor for executing the specified querier.

    @tparam QUERIER
        The type of the querier.

    @param querier
        The querier instance to execute.

    @return
        A new executor instance for the specified querier.

    @throw sqt::SQLError
        Thrown if an error occurs during the creation of the executor.

    @details
        This method is used to execute queriers created by the `Make*()` methods. It prepares 
        the corresponding SQL statement for the querier and binds all inline parameters in the 
        querier to the statement. The returned executor can then be used to bind placeholder 
        parameters and execute the statement.

        For more information about using the executor, refer to the `sqt::Executor<>` class.

        Calling this method will initialize the associated database table.

    @see sqt::DataContext<>::InitializeTable()
    @see sqt::Executor<>
    @see sqt::QuerierType
    */
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

        For more control over the conflict action and the inserted columns, use the more flexible 
        `MakeInserter()` and `MakeInserter(ASSIGNMENT&&...)` methods from the complex style 
        interface.

    @see sqt::DataContext<>::AutoIncInsert()
    @see sqt::DataContext<>::AutoIncReplace()
    @see sqt::DataContext<>::MakeInserter()
    @see sqt::DataContext<>::MakeInserter(ASSIGNMENT&&... assignments)
    @see sqt::DataContext<>::Replace()
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

        For more control over the conflict action, use the more flexible `MakeAutoIncInserter()` 
        method from the complex style interface.

    @see sqt::DataContext<>::AutoIncReplace()
    @see sqt::DataContext<>::Insert()
    @see sqt::DataContext<>::MakeAutoIncInserter()
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
        if an unique constraint violation occurs.

        To automatically generate the primary key value, use `AutoIncReplace()` method instead.

        For more control over the inserted columns, use the more flexible 
        `MakeReplacer(ASSIGNMENTS&&...)` method from the complex style interface.

    @see sqt::DataContext<>::AutoIncReplace()
    @see sqt::DataContext<>::Insert()
    @see sqt::DataContext<>::MakeReplacer()
    @see sqt::DataContext<>::MakeReplacer(ASSIGNMENTS&&... assignments)
    */
    std::int64_t Replace(const ENTITY& entity) {
        constexpr auto replacer = MakeReplacer();
        return ExecuteEntityInserter(replacer, entity);
    }


    /**
    Inserts the specified entity into the database table, automatically generating the primary key
    value and replacing the existing row.

    @param entity
        The entity to be inserted.

    @return
        The generated row ID of the inserted entity.

    @throw sqt::SQLError
        Thrown if the insertion fails.

    @details
        This method is similar to the `AutoIncInsert()` method, except that it replaces the 
        existing row if an unique constraint violation occurs.

        @note
        This method is only available if the entity type has an auto-incremented primary key. Use
        the `SQT_PRIMARY_KEY_AUTO_INC` macro to define an auto-incremented primary key.

    @see sqt::DataContext<>::AutoIncInsert()
    @see sqt::DataContext<>::MakeAutoIncReplacer()
    @see SQT_PRIMARY_KEY_AUTO_INC
    */
    std::int64_t AutoIncReplace(const ENTITY& entity) requires AutoIncEntityValueType<ENTITY> {
        constexpr auto replacer = MakeAutoIncReplacer();
        return ExecuteEntityInserter(replacer, entity);
    }

    /**
    Updates the specified entity in the database table.

    @param entity
        The entity to be updated. Its primary key value is used to identify the entity.

    @return
        `true` if the entity was updated; otherwise, `false` if the entity does not exist in the 
        table.

    @throw sqt::SQLError
        Thrown if the update fails.

    @details
        @note
        This method is only available if the entity type has a primary key. Use the 
        `SQT_PRIMARY_KEY` or `SQT_PRIMARY_KEY_AUTO_INC` macro to define a primary key.

        This method updates the row whose primary key value matches the primary key value of the 
        specified entity. All non-primary key columns will be updated. For more control over the 
        update conditions or the specific columns to be updated, use the following methods from the
        complex style interface:
        - `MakeUpdater()` for creating an updater that updates all columns of the entity type and 
          can be applied with update conditions.
        - `MakeNoPrimaryKeyUpdater()`, similar to `MakeUpdater()`, except that it updates only
          non-primary key columns.
        - `MakeUpdater(ASSIGNMENTS&&...)` for creating an updater that updates specific columns, 
          and can also be applied with update conditions.

    @see sqt::DataContext<>::MakeNoPrimaryKeyUpdater()
    @see sqt::DataContext<>::MakeUpdater()
    @see sqt::DataContext<>::MakeUpdater(ASSIGNMENTS&&... assignments)
    @see SQT_PRIMARY_KEY
    @see SQT_PRIMARY_KEY_AUTO_INC
    */
    bool Update(const ENTITY& entity) requires PrimaryKeyEntityValueType<ENTITY> {
        constexpr auto updater = 
            MakeNoPrimaryKeyUpdater().Where(Table<ENTITY>.PrimaryKey == sqt::_);
        auto executor = Prepare(updater);
        executor.BeginBind().Bind(entity).BindFromEntity(entity);
        executor.Execute();
        return executor.LastChanges() > 0;
    }

    /**
    Deletes all rows from the database table.

    @return
        The number of rows deleted.

    @throw sqt::SQLError
        Thrown if the deletion fails.

    @details
        This method empties the entire table. For more control over which rows to delete, use the 
        following alternatives:

        - `Delete()` for deleting a row by the specified primary key value.
        - `MakeDeleter()` for creating a deleter that can be applied with custom conditions.

    @see sqt::DataContext<>::Delete()
    @see sqt::DataContext<>::MakeDeleter()
    */
    std::size_t DeleteAll() {
        constexpr auto deleter = MakeDeleter();
        auto executor = Prepare(deleter);
        executor.Execute();
        return executor.LastChanges();
    }

    /**
    Deletes a row by the specified primary key value from the database table.

    @param primary_key
        The primary key value of the row to be deleted.

    @return
        `true` if the row was deleted; otherwise, `false` if the row with the specified primary key
        value does not exist.

    @throw sqt::SQLError
        Thrown if the deletion fails.

    @details
        @note
        This method is only available if the entity type has a primary key. Use the 
        `SQT_PRIMARY_KEY` or `SQT_PRIMARY_KEY_AUTO_INC` macro to define a primary key.

        For more control over the conditions of which rows to delete, use the `MakeDeleter()` 
        method from the complex style interface to create a deleter and apply custom conditions.

    @see sqt::DataContext<>::DeleteAll()
    @see sqt::DataContext<>::MakeDeleter()
    @see SQT_PRIMARY_KEY
    @see SQT_PRIMARY_KEY_AUTO_INC
    */
    template<typename E = ENTITY> requires PrimaryKeyEntityValueType<E>
    bool Delete(const typename TableType<E>::PrimaryKeyType::ValueType& primary_key) {

        constexpr auto deleter = MakeDeleter().Where(Table<E>.PrimaryKey == sqt::_);
        auto executor = Prepare(deleter);
        executor.BeginBind().Bind(primary_key);
        executor.Execute();
        return executor.LastChanges() > 0;
    }

    /**
    Retrieves all entities from the database table.

    @return
        A container holding all entities in the table.

    @throw sqt::SQLError
        Thrown if the selection fails.

    @details
        This method retrieves all entities into a container. Be aware that this may result in high 
        memory consumption if the table contains a large number of rows. To mitigate this, consider
        using the `MakeSelecter()` method from the complex style interface to control the selection 
        progress manually.

        For more control over which entities to retrieve, use the following alternatives:
        - `Select()` for retrieving a single entity by the specified primary key value.
        - `MakeSelecter()` for creating a selecter that can be applied with custom conditions.

    @see sqt::DataContext<>::MakeSelecter()
    @see sqt::DataContext<>::MakeSelecter(const COLUMNS&... columns)
    @see sqt::DataContext<>::Select()
    */
    std::vector<ENTITY> SelectAll() {
        constexpr auto selecter = MakeSelecter();
        auto executor = Prepare(selecter);
        auto result = executor.Execute();
        return std::vector<ENTITY>{ result.begin(), result.end() };
    }

    /**
    Retrieves a single entity by the specified primary key value from the database table.

    @param primary_key
        The primary key value of the entity to be retrieved.

    @return
        The entity if found; otherwise, `std::nullopt` if the entity with the specified primary key
        value does not exist.

    @throw sqt::SQLError
        Thrown if the selection fails.

    @details
        @note
        This method is only available if the entity type has a primary key. Use the 
        `SQT_PRIMARY_KEY` or `SQT_PRIMARY_KEY_AUTO_INC` macro to define a primary key.

        For more control over which entities to retrieve, use the `MakeSelecter()` method from the
        complex style interface to create a selecter and apply custom conditions. Furthermore, use 
        the `MakeSelecter(const COLUMNS&...)` method to specify which columns of the entity to
        select.

    @see sqt::DataContext<>::MakeSelecter()
    @see sqt::DataContext<>::MakeSelecter(const COLUMNS&... columns)
    @see sqt::DataContext<>::SelectAll()
    @see SQT_PRIMARY_KEY
    @see SQT_PRIMARY_KEY_AUTO_INC
    */
    template<typename E = ENTITY> requires PrimaryKeyEntityValueType<E>
    std::optional<E> Select(const typename TableType<E>::PrimaryKeyType::ValueType& primary_key) {

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
