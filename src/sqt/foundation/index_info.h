#pragma once

/**
@file
    Defines the `sqt::IndexInfo` struct.
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