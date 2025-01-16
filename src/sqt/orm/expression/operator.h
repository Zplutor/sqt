#pragma once

#include <string_view>

namespace sqt {

enum class Operator {
    Equal,
    NotEqual,
    Less,
    LessEqual,
    Greater,
    GreaterEqual,
    And,
    Or,
};

std::string_view ConvertOperatorToString(Operator op);

}