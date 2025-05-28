#pragma once

/**
@file
    Defines the `sqt::AssignmentOperator` enum.
*/

namespace sqt {

/**
Represents the assignment operator used in assignments.

@details
    This enum is used as a tag for checking if a type is an assignment type. The enum value is 
    meaningless and is not used.

@see sqt::Assignment<>
@see sqt::AssignmentType
*/
enum class AssignmentOperator {
    Assign,
};

}