#pragma once

namespace sqt {

enum class ConflictAction {
    Abort,
    Fail,
    Ignore,
    Replace,
    Rollback,
};

}