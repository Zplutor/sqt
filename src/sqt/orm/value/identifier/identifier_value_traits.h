#pragma once

/**
@file
    Defines the `sqt::IdentifierValueTraits<> class template.
*/

#include <sqt/foundation/statement.h>
#include <sqt/orm/table/identifier_type.h>

namespace sqt {

/**
Defines traits for the value type of an identifier.

@tparam IDENTIFIER
    A type that satisfies the `sqt::IdentifierType` concept. It can be a column type, primary key
    type or index type.

@details
    This traits type is a wrapper around the traits type of the identifier's value type, providing
    additional functionality for binding and retrieving values from SQL statements.

    This class template satisfies the `sqt::IdentifierValueTraitsType` concept.

@see sqt::IdentifierType
@see sqt::IdentifierValueTraitsType
*/
template<IdentifierType IDENTIFIER>
class IdentifierValueTraits {
public:
    using IdentifierType = IDENTIFIER;
    using EntityType = typename IDENTIFIER::EntityType;
    using ValueType = typename IDENTIFIER::ValueType;

    /**
    Binds a value to the statement at the specified parameter index.

    @param statement
        The statement to which the value is bound.

    @param parameter_index
        The index of the parameter to which the value is bound.

    @param value
        The value to bind.

    @details
        This method delegates to the `BindValue()` method of the value traits type associated with 
        the identifier.
    */
    static void BindValue(Statement& statement, int parameter_index, const ValueType& value) {
        IDENTIFIER::ValueTraits::BindValue(statement, parameter_index, value);
    }

    /**
    Binds a value from an entity to the statement at the specified parameter index.

    @param statement
        The statement to which the value is bound.

    @param parameter_index
        The index of the parameter to which the value is bound.

    @param entity
        The entity from which the value is extracted.

    @details
        This method extracts the value from the entity using the `ValueSource` of the identifier 
        and calls the `BindValue()` method to bind the value to the statement.
    */
    static void BindValueFromEntity(
        Statement& statement, 
        int parameter_index, 
        const EntityType& entity) {

        const auto& value = IDENTIFIER::ValueSource::GetValueFromEntity(entity);
        BindValue(statement, parameter_index, value);
    }

    /**
    Retrieves a value from the statement at the specified column index.

    @param statement
        The statement from which the value is retrieved.

    @param column_index
        The index of the column from which the value is retrieved.

    @details
        This method delegates to the `RetrieveValue()` method of the value traits type associated 
        with the identifier.
    */
    static ValueType RetrieveValue(const Statement& statement, int column_index) {
        return IDENTIFIER::ValueTraits::RetrieveValue(statement, column_index);
    }

    /**
    Retrieves a value from the statement and sets it to the entity.

    @param statement
        The statement from which the value is retrieved.

    @param column_index
        The index of the column from which the value is retrieved.

    @param entity
        The entity to which the value is set.

    @details
        This method calls the `RetrieveValue()` method to retrieve the value from the statement and
        then sets it to the entity using the `ValueSource` of the identifier.
    */
    static void RetrieveValueToEntity(
        const Statement& statement, 
        int column_index,
        EntityType& entity) {

        auto value = RetrieveValue(statement, column_index);
        IDENTIFIER::ValueSource::SetValueToEntity(entity, std::move(value));
    }
};

}