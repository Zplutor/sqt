#pragma once

/**
@file
    Defines the class `sqt::Database`.
*/

#include <filesystem>
#include <sqlite3.h>
#include <sqt/foundation/index_info.h>
#include <sqt/foundation/statement.h>
#include <sqt/foundation/transaction.h>
#include <sqt/foundation/table_info.h>

namespace sqt {

/**
Wrapper class for SQLite database.
*/
class Database {
public:
    /**
    Opens a SQLite database at the specified file path.

    @param path
        The file path at which the database opens. The file will be created if it doesn't exist.

    @return
        An opened `sqt::Database` instance.

    @throws sqt::SQLError
        Thrown if fails to open the database.
    */
    static Database Open(const std::filesystem::path& path);

public:
    /**
    Constructs an instance with the specified SQLite database handle.

    @param handle
        The SQLite database handle. The ownership of the handle is transferred to the constructed 
        instance.
    */
    explicit Database(sqlite3* handle) noexcept;

    /**
    Destructs the instance.

    @details
        The SQLite database handle will be closed.
    */
    ~Database();

    Database(Database&) = delete;
    Database& operator=(const Database&) = delete;

    Database(Database&& other) noexcept;
    Database& operator=(Database&& other) noexcept;

    /**
    Prepares the specified SQL statement.

    @param sql
        The SQL statement to prepare.

    @return
        A prepared `sqt::Statement` instance. The instance is valid until the current database is
        destroyed.

    @throw sqt::SQLError
        Thrown if fails to prepare the SQL statement.

    @details
        Consider reusing the returned statement instance for the same SQL statement in a batch
        operation to gain the best performance.
    */
    Statement PrepareStatement(std::string_view sql);

    /**
    Executes the specified SQL statement.

    @param sql
        The SQL statement to execute.

    @throw sqt::SQLError
        Thrown if fails to execute the SQL statement.

    @details
        This method is equivalent to calling:
        @code
        auto statement = PrepareStatement(sql);
        statement.Step();
        @endcode

        A statement is created and destroyed every time this method is called. If the same SQL
        statement needs to be executed multiple times in a batch operation, consider using
        `PrepareStatement` and reuse the returned statement instance.

    @see sqt::Database::PrepareStatement()
    */
    void ExecuteSQL(std::string_view sql);

    /**
    Begins a transaction.

    @return
        A `sqt::Transaction` instance used to commit or roll back the transaction. The instance is
        valid until the current database is destroyed.

    @throw sqt::SQLError
        Thrown if fails to begin the transaction.
    */
    [[nodiscard]]
    Transaction BeginTransaction();

    /**
    Gets the inserted row ID by the most recent successful insert statement.

    @return
        The inserted row ID. If no successful insert statement has been executed, the return
        value is 0.
    */
    std::int64_t LastInsertRowID() const noexcept;

    /**
    Gets the number of rows changed by the most recent successful insert, update, or delete 
    statement.

    @return
        The number of rows changed.
    */
    std::size_t LastChanges() const noexcept;

    /**
    Gets information of the specified table.

    @param table_name
        The name of the table.

    @return
        The table information if the table exists; otherwise null.

    @throw sqt::SQLError
        Thrown if fails to get the table information.

    @details
        This method executes the `pragma table_info` statement to get the table information.
    */
    std::optional<TableInfo> GetTableInfo(std::string_view table_name);

    /**
    Gets information of the specified index.

    @param index_name
        The name of the index.

    @return
        The index information if the index exists; otherwise null.

    @throw sqt::SQLError
        Thrown if fails to get the index information.

    @details
        This method executes the `pragma index_info` statement to get the index information.
    */
    std::optional<IndexInfo> GetIndexInfo(std::string_view index_name);

    /**
    Gets the SQLite database handle.

    @return
        The SQLite database handle.
    */
    sqlite3* Handle() const noexcept {
        return handle_;
    }

private:
    void Reset() noexcept;

private:
    sqlite3* handle_{};
};

}