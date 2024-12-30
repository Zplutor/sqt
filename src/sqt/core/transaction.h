#pragma once

namespace sqt {

class Database;

class Transaction {
public:
    explicit Transaction(Database& database);
    ~Transaction();

    Transaction(const Transaction&) = delete;
    Transaction& operator=(const Transaction&) = delete;

    Transaction(Transaction&& other) noexcept;
    Transaction& operator=(Transaction&& other) noexcept;

    void Commit();
    void Rollback();

private:
    void TryToRollback() noexcept;

private:
    Database* database_{};
};

}