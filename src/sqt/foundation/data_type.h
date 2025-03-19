#pragma once

/**
@file
    Defines the enum `sqt::DataType`.
*/

#include <string_view>
#include <sqlite3.h>

namespace sqt {

/**
Represents the type of data for an individual column.
*/
enum class DataType {

    /**
    Integral type.
    */
    Integer = SQLITE_INTEGER,

    /**
    Floating point type.
    */
    Float = SQLITE_FLOAT,

    /**
    UTF-8 encoded text type.
    */
    Text = SQLITE_TEXT,

    /**
    Binary data type.
    */
    BLOB = SQLITE_BLOB,

    /**
    Null data.
    */
    Null = SQLITE_NULL,
};


/**
Provides utility functions for working with `sqt::DataType`.
*/
class DataTypeTraits {
public:
    /**
    Converts the specified `sqt::DataType` value to a string.

    @param data_type
        The value to be converted.

    @return
        A string for the specified value. If the value is not recognized, an empty string is 
        returned.

    @details
        The conversion follows the following mapping:
        - `sqt::DataType::Integer` -> `integer`
        - `sqt::DataType::Float` -> `float`
        - `sqt::DataType::Text` -> `text`
        - `sqt::DataType::BLOB` -> `blob`

        `sqt::DataType::Null` will be converted to an empty string.
    */
    static std::string_view ToString(DataType data_type) noexcept;

    /**
    Converts the specified string to a `sqt::DataType` value.

    @param string
        The string to be converted. The comparison is case-insensitive.

    @return
        A `sqt::DataType` value for the specifed string. If the string is not recognized,
        `sqt::DataType::Null` is returned.

    @see sqt::DataTypeTraits::ToString
    */
    static DataType FromString(std::string_view string) noexcept;

private:
    DataTypeTraits() = delete;
};

}