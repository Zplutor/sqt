#pragma once

/**
@file
    Defines the `sqt::IdentifierOperand<>` primary template and its specializations.
*/

#include <sqt/foundation/statement.h>
#include <sqt/orm/table/column/column_type.h>
#include <sqt/orm/table/column/composite_column_type.h>

namespace sqt {

/**
Base class for identifier operands.

@tparam IDENTIFIER
    The identifier type this operand represents.

@details
    This base class provides the common implementation for identifier operands. It is inherited by
    the specializations of the `sqt:IdentifierOperand<>` template.

@see sqt::IdentifierOperand<>
@see sqt::IdentifierOperand<COLUMN>
@see sqt::IdentifierOperand<COMPOSITE_COLUMN>
*/
template<typename IDENTIFIER>
class BaseIdentifierOperand {
public:
    using IdentifierType = IDENTIFIER;
    using EntityType = typename IDENTIFIER::EntityType;

    static constexpr std::size_t ParameterCount = 0;

    static constexpr std::tuple<> BuildPlaceholderBinders(int parameter_index) noexcept {
        return {};
    }

public:
    constexpr void BindInlineParameters(Statement& statement, int parameter_index) const noexcept {

    }

protected:
    constexpr BaseIdentifierOperand() noexcept = default;
};


/**
The primary template for defining identifier operands.

@tparam IDENTIFIER
    The identifier type this operand represents.

@details
    This primary template is used to define identifier operands. There are two specializations of 
    this template depending on the identifier type:
    - `sqt::IdentifierOperand<COLUMN>` for single column.
    - `sqt::IdentifierOperand<COMPOSITE_COLUMN>` for composite column.

@see sqt::IdentifierOperand<COLUMN>
@see sqt::IdentifierOperand<COMPOSITE_COLUMN>
*/
template<typename IDENTIFIER>
class IdentifierOperand;


/**
The specialization of the `sqt::IdentifierOperand<>` template for single column.

@tparam COLUMN
    The column type this operand represents, which must satisfy the `sqt::ColumnType` concept.

@see sqt::ColumnType
@see sqt::IdentifierOperand<>
@see sqt::IdentifierOperand<COMPOSITE_COLUMN>
*/
template<ColumnType COLUMN>
class IdentifierOperand<COLUMN> : public BaseIdentifierOperand<COLUMN> {
public:
    static std::string BuildSQL() {
        return std::string{ COLUMN::Name };
    }

public:
    constexpr IdentifierOperand() noexcept = default;
};


/**
The specialization of the `sqt::IdentifierOperand<>` template for composite column.

@tparam COMPOSITE_COLUMN
    The composite column type this operand represents, which must satisfy the
    `sqt::CompositeColumnType` concept.

@details
    This specialization can be used for primary keys and indexes as they are defined as composite
    columns.

@see sqt::CompositeColumnType
@see sqt::IdentifierOperand<>
@see sqt::IdentifierOperand<COLUMN>
*/
template<CompositeColumnType COMPOSITE_COLUMN>
class IdentifierOperand<COMPOSITE_COLUMN> : public BaseIdentifierOperand<COMPOSITE_COLUMN> {
public:
    static std::string BuildSQL() {
        return COMPOSITE_COLUMN::BuildColumnNames();
    }

public:
    constexpr IdentifierOperand() noexcept = default;
};

}