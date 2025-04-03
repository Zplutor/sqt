#pragma once

/**
@file
    Defines the `sqt::StepResult` class.
*/

namespace sqt {

/**
Return type of `sqt::Statement::Step`, providing methods to check whether the statement has more 
rows to step forward.
*/
class StepResult {
public:
    /**
    Constructs an instance with a value indicating whether the statement has more rows to step 
    forward.

    @param has_more
        The indicating value.
    */
    explicit StepResult(bool has_more) noexcept : has_more_(has_more) {

    }

    /**
    Indicates whether the statement has more rows to step forward.

    @return
        `true` if the statement has more rows to step forward; otherwise `false`.

    @details
        For non-select statements, this method always returns `false`.
    */
    bool HasMore() const noexcept {
        return has_more_;
    }

private:
    bool has_more_{};
};

}