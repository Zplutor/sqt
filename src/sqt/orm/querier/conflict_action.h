#pragma once

/**
@file
    Defines the `sqt::ConflictAction` enum.
*/

#include <string_view>

namespace sqt {

/**
Conflict action to be used when an unique constraint violation occurs during an insert or update
operation.

@details
    The enum values are defined according to the SQLite documentation for the `ON CONFLICT` clause.
    For more information, see https://www.sqlite.org/lang_conflict.html.
*/
enum class ConflictAction {

    /**
    Aborts the current SQL statement with an error and backs out any changes made by the current 
    SQL statement without rolling back the current transaction.
    */
    Abort,

    /**
    Aborts the current SQL statement with an error without backing out prior changes and rolling 
    back the current transaction.
    */
    Fail,

    /**
    Skips the current row and continues processing subsequent rows of the SQL statement.
    */
    Ignore,

    /**
    Deletes the pre-existing rows and continues executing the SQL statement.
    */
    Replace,

    /**
    Aborts the current SQT statement with an error and rolls back the current transaction.
    */
    Rollback,
};



/**
Provides utility functions for working with the `sqt::ConflictAction` enum.
*/
class ConflictActionEnum {
public:
    /**
    Converts the specified `sqt::ConflictAction` value to a string.

    @param action
        The value to be converted.

    @return
        A string for the specified value. If the value is not recognized, an empty string is 
        returned.

    @details
        The conversion follows the following mapping:
        |Value                          |String    |
        |-------------------------------|----------|
        |`sqt::ConflictAction::Abort`   |`abort`   |
        |`sqt::ConflictAction::Fail`    |`fail`    |
        |`sqt::ConflictAction::Ignore`  |`ignore`  |
        |`sqt::ConflictAction::Replace` |`replace` |
        |`sqt::ConflictAction::Rollback`|`rollback`|
    */
    static constexpr std::string_view ToString(ConflictAction action) noexcept {
        switch (action) {
        case ConflictAction::Abort:
            return "abort";
        case ConflictAction::Fail:
            return "fail";
        case ConflictAction::Ignore:
            return "ignore";
        case ConflictAction::Replace:
            return "replace";
        case ConflictAction::Rollback:
            return "rollback";
        default:
            return "";
        }
    }

public:
    ConflictActionEnum() = delete;
};

}