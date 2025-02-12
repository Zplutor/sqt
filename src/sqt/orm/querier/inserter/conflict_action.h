#pragma once

#include <string_view>

namespace sqt {

enum class ConflictAction {
    Abort,
    Fail,
    Ignore,
    Replace,
    Rollback,
};

constexpr inline std::string_view ConvertConflictActionToString(ConflictAction action) {
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

}