#pragma once

#include <tuple>
#include <sqt/foundation/statement.h>
#include <sqt/orm/expression/assignment_type.h>

namespace sqt::internal {

template<AssignmentType... ASSIGNMENT>
void BindAssignmentInlineParameters(
    Statement& statement, 
    int begin_index,
    const std::tuple<ASSIGNMENT...>& assignments) {

    int index = begin_index;
    auto bind = [&statement, &index](const auto& assignment) {
        assignment.BindInlineParameters(statement, index);
        index += assignment.ParameterCount;
    };

    std::apply(
        [&bind](const auto&... values) {
            (bind(values), ...);
        },
        assignments);
}

}