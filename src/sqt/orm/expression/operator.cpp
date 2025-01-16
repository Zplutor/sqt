#include <sqt/orm/expression/operator.h>

namespace sqt {

std::string_view ConvertOperatorToString(Operator op) {
    switch (op) {
    case Operator::Equal:
        return "=";
    case Operator::NotEqual:
        return "<>";
    case Operator::Less:
        return "<";
    case Operator::LessEqual:
        return "<=";
    case Operator::Greater:
        return ">";
    case Operator::GreaterEqual:
        return ">=";
    case Operator::And:
        return "and";
    case Operator::Or:
        return "or";
    default:
        return "";
    }
}

}