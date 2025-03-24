#pragma once

/**
@file
    Defines the class `sqt::Transaction`.
*/

namespace sqt {

class Database;

/**
Represents an ongoing transaction on a database, providing methods to commit or roll back the
transaction.
*/
class Transaction {
public:
    /**
    Constructs an instance with the specified database.

    @param database
        The database which has already began a transaction.

    @note
        Don't call this constructor directly. Use `sqt::Database::BeginTransaction` to begin a 
        transaction.

    @see `sqt::Database::BeginTransaction()`
    */
    explicit Transaction(Database& database) noexcept;

    /**
    Destructs the instance, rolling back the transaction if needed.

    @details
        The transaction will be rolled back automatically if it is not committed or not rolled back
        manually.
    */
    ~Transaction();

    Transaction(const Transaction&) = delete;
    Transaction& operator=(const Transaction&) = delete;

    Transaction(Transaction&& other) noexcept;
    Transaction& operator=(Transaction&& other) noexcept;

    /**
    Commits the transaction.

    @throw sqt::SQLError
        Thrown if fails to commit the transaction.
    */
    void Commit();

    /**
    Rolls back the transaction.

    @throw sqt::SQLError
        Thrown if fails to roll back the transaction.
    */
    void Rollback();

private:
    void TryToRollback() noexcept;

private:
    Database* database_{};
};

}