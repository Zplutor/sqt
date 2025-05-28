#pragma once

/**
@file
    Defines the `sqt::ExpressionLike` concept.
*/

#include <concepts>
#include <string>
#include <sqt/foundation/statement.h>
#include <sqt/orm/expression/binder/binder_chain.h>
#include <sqt/orm/expression/binder/binder_tuple_type.h>

namespace sqt {

/**
Constrains a type to be an expression-like type.

@details
    @b Requirements
    - The type must have a static constant `ParameterCount` of type `std::size_t`, representing
      the number of parameters in the expression (including inline parameters and placeholders).

    - The type must have a static method `BuildPlaceholderBinders()` with the following signature:
      @code{.cpp}
      auto BuildPlaceholderBinders(int parameter_index);
      @endcode
      The return type must satisfy the `sqt::BinderTupleType` concept. This method creates binders
      for placeholders in the expression, starting from the given parameter index.

    - The type must have a static method `BuildSQL()` with the following signature:
      @code{.cpp}
      std::string BuildSQL();
      @endcode
      This method creates a string representing the expression in SQL.

    - The type must have a member method `BindInlineParameters()` with the following signature:
      @code{.cpp}
      void BindInlineParameters(Statement& statement, int parameter_index) const;
      @endcode
      This method binds inline parameters in the expression to the SQL statement, starting from 
      the given parameter index.

    This concept defines the common requirements for expression-like types, which are used in
    various circumstances require expressions. There are several concepts for more specific
    expression types defined in the framework:
    - `sqt::AssignmentType` for assignments.
    - `sqt::PredicateType` for predicates.
    - `sqt::OrderingTermType` for ordering terms.
    - `sqt::OperandType` for operands.

@see sqt::AssignmentType
@see sqt::BinderTupleType
@see sqt::OrderingTermType
@see sqt::OperandType
@see sqt::PredicateType
*/
template<typename T>
concept ExpressionLike = requires(const T t, Statement& statement, int parameter_index) {
    { T::ParameterCount } -> std::same_as<const std::size_t&>;
    { T::BuildPlaceholderBinders(parameter_index) } -> BinderTupleType;
    { T::BuildSQL() } -> std::same_as<std::string>;
    { t.BindInlineParameters(statement, parameter_index) } -> std::same_as<void>;
};

}