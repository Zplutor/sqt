#pragma once

/**
@file
    Defines the `sqt::Transaction` class.
*/

namespace sqt {

class Database;

/**
Represents an ongoing transaction on a database, providing methods to commit or roll back the
transaction.

@details
    To begin a transaction, use the `sqt::Database::BeginTransaction()` method, which returns a 
    `sqt::Transaction` instance. To commit the transaction, call the `Commit()` method explicitly. 
    To roll back the transaction, either call the `Rollback()` method explicitly or let the 
    `sqt::Transaction` instance go out of scope, which will automatically roll back the 
    transaction.

@see sqt::Database::BeginTransaction()
*/
class Transaction {
public:
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
    friend class Database;

    explicit Transaction(Database& database) noexcept;

    void TryToRollback() noexcept;

private:
    Database* database_{};
};

}