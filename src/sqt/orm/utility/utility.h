#pragma once

#include <string>

namespace sqt {

template<typename VIEW>
std::string JoinColumnNames(VIEW columns) {
    std::string result;
    for (std::size_t index = 0; index < columns.size(); ++index) {
        if (index != 0) {
            result += ',';
        }
        result += columns[index]->GetName();
    }
    return result;
}


std::string JoinPlaceholders(std::size_t count);

}