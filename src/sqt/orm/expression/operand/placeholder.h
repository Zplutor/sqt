#pragma once

/**
@file
    Defines the `sqt::Placeholder` struct and the `sqt::_` constant.
*/

namespace sqt {

/**
Represents a placeholder in an expression.

@details
    This struct is a tag type to indicate a placeholder in an expression. The `sqt::_` constant is 
    a helper to create an expression contains a placeholder.

@see sqt::PlaceholderOperand<>
@see sqt::_
*/
struct Placeholder {

};


/**
A helper constant to create an expression containing a placeholder.

@see sqt::Placeholder
@see sqt::PlaceholderOperand<>
*/
constexpr Placeholder _;

}