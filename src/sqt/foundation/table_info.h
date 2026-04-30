#pragma once

/**
@file
    Defines data structures for table information.
*/

#include <string>
#include <vector>
#include <sqt/foundation/data_type.h>

namespace sqt {

/**
Contains the information of a column.
*/
struct ColumnInfo {

    /**
    The name of the column.
    */
    std::string name;

    /**
    The data type of the column.
    */
    DataType data_type{ DataType::Null };

    /**
    Whether the column is a part of the primary key.
    */
    bool is_primary_key{};

    /**
    Whether the column is nullable.
    */
    bool is_nullable{};

    /**
    The default value expression for the column.
    */
    std::string default_value_expression;
};


/**
Contains the information of a table.
*/
struct TableInfo {

    /**
    The information for all columns within the table.
    */
    std::vector<ColumnInfo> columns;
};

}