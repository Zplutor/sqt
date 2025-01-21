#pragma once

#include <stdexcept>
#include <sqlite3.h>

namespace sqt {

class SQLError : public std::runtime_error {
public:
    SQLError(int code, const char* message) : runtime_error(message), code_(code) {

    }

    int Code() const noexcept {
        return code_;
    }

private:
    int code_{};
};


[[noreturn]]
inline void ThrowSQLError(int error_code, sqlite3* db_handle) {
    const char* message{};
    if (db_handle) {
        message = sqlite3_errmsg(db_handle);
    }
    throw SQLError{ error_code, (message ? message : "") };
}


#define SQT_THROW_IF_SQL_ERROR(error_code, db_handle) \
if (error_code != SQLITE_OK) sqt::ThrowSQLError(error_code, db_handle);

}