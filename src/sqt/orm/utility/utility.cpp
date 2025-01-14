#include <sqt/orm/utility/utility.h>

namespace sqt {

std::string JoinColumnNames(AbstractColumnsView columns) {

    std::string result;
    for (std::size_t index = 0; index < columns.size(); ++index) {

        if (index != 0) {
            result += ',';
        }
        result += columns[index]->GetName();
    }
    return result;
}


std::string JoinPlaceholders(std::size_t count) {

    std::string result;
    for (std::size_t index = 0; index < count; ++index) {

        if (index != 0) {
            result += ',';
        }
        result += '?';
    }
    return result;
}

}