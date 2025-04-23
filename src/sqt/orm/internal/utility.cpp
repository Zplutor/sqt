#include <sqt/orm/internal/utility.h>

namespace sqt::internal {

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