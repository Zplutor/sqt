#pragma once

/**
@file
    Defines the struct `sqt::IndexInfo`.
*/

#include <string>
#include <vector>

namespace sqt {

/**
Contains the information of an index.
*/
struct IndexInfo {

    /**
    The column names within the index.
    */
    std::vector<std::string> columns;
};

}