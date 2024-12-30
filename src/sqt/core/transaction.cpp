#include <sqt/core/transaction.h>
#include <sqt/core/database.h>

namespace sqt {

Transaction::Transaction(Database& database) {

    database.ExecuteSQL("begin transaction");
    database_ = &database;
}


Transaction::~Transaction() {
    TryToRollback();
}


Transaction::Transaction(Transaction&& other) noexcept : database_(other.database_) {
    other.database_ = nullptr;
}


Transaction& Transaction::operator=(Transaction&& other) noexcept {

    if (this != &other) {

        TryToRollback();

        database_ = other.database_;
        other.database_ = nullptr;
    }
    return *this;
}


void Transaction::Commit() {
    database_->ExecuteSQL("commit transaction");
    database_ = nullptr;
}


void Transaction::Rollback() {
    database_->ExecuteSQL("rollback transaction");
    database_ = nullptr;
}


void Transaction::TryToRollback() noexcept {

    try {
        if (database_) {
            Rollback();
        }
    }
    catch (...) {

    }
}

}