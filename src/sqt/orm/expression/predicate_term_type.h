#pragma once

/**
@file
    Defines the `sqt::PredicateTermType` concept.
*/

#include <sqt/orm/expression/operand/operand_type.h>
#include <sqt/orm/expression/predicate_type.h>

namespace sqt {

/**
Constrains a type to be a predicate term type.

@details
    @b Requirements
    - The type must satisfy the `sqt::OperandType` concept or the `sqt::PredicateType` concept.

    Predicate terms are operands of predicates.
   
@see sqt::OperandType
@see sqt::PredicateType
*/
template<typename T>
concept PredicateTermType = OperandType<T> || PredicateType<T>;

}