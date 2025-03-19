#pragma once

/**
@file
    Defines exception class and related facilities for SQLite errors.
*/

#include <stdexcept>
#include <sqlite3.h>

namespace sqt {

/**
Exception class for SQLite errors.
*/
class SQLError : public std::runtime_error {
public:
    /**
    Constructs an exception instance with the specified error code and message.

    @param code
        The error code returned by SQLite functions.

    @param message
        The message for the error.
    */
    SQLError(int code, const char* message) : runtime_error(message), code_(code) {

    }

    /**
    Gets the SQLite error code.
    */
    int Code() const noexcept {
        return code_;
    }

private:
    int code_{};
};


/**
A helper function to throw the `sqt::SQLError` exception.

@param error_code
    The error code returned by SQLite functions.

@param db_handle
    The SQLite database handle from which the error message is retrieved.
*/
[[noreturn]]
inline void ThrowSQLError(int error_code, sqlite3* db_handle) {
    const char* message{};
    if (db_handle) {
        message = sqlite3_errmsg(db_handle);
    }
    throw SQLError{ error_code, (message ? message : "") };
}


/**
A helper macro to throw the `sqt::SQLError` exception if the specified error code is not
`SQLITE_OK`.

@param error_code
    The error code returned by SQLite functions.

@param db_handle
    The SQLite database handle from which the error message is retrieved.
*/
#define SQT_THROW_IF_SQL_ERROR(error_code, db_handle) \
if (error_code != SQLITE_OK) sqt::ThrowSQLError(error_code, db_handle);

}