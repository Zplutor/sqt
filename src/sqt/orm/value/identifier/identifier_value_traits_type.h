#pragma once

/**
@file
    Defines the `sqt::IdentifierValueTraitsType` concept.
*/

#include <sqt/orm/value/value_traits_type.h>

namespace sqt {

/**
Constrains a type to be an identifier value traits type, which associates a column, primary key, or
index with its corresponding value traits type.

@details
    @b Requirements
    - The type must satisfy the `sqt::ValueTraitsType` concept.
    - The type must have a nested type `IdentifierType`, representing the type of a column, 
      primary key, or index.
    - The type must have a nested type `EntityType`, representing the entity type to which the 
      `IdentifierType` belongs.
    - The type must have a static method `BindValueFromEntity()` with the following signature:
      @code{.cpp}
      static void BindValueFromEntity(
          sqt::Statement& statement, 
          int parameter_index, 
          const EntityType& entity);
      @endcode
    - The type must have a static method `RetrieveValueToEntity()` with the following signature:
      @code{.cpp}
      static void RetrieveValueToEntity(
          const sqt::Statement& statement, 
          int column_index, 
          EntityType& entity);
      @endcode

    Identifier value traits types are wrappers around columns, primary keys, or indexes. These 
    traits types provide both the identifier type and the entity type, enabling the framework to 
    bind and retrieve values directly through an entity, rather than requiring manual extraction 
    of the values.

    The `sqt::IdentifierValueTraits<>` class template satisfies this concept.

@see sqt::IdentifierValueTraits<>
@see sqt::ValueTraitsType
*/
template<typename T>
concept IdentifierValueTraitsType = 
    ValueTraitsType<T> && 
    requires {
        typename T::IdentifierType;
        typename T::EntityType;
    } &&
    requires (Statement& statement, int parameter_index, const typename T::EntityType& entity) {
        { T::BindValueFromEntity(statement, parameter_index, entity) } -> std::same_as<void>;
    } &&
    requires (const Statement& statement, int column_index, typename T::EntityType& entity) {
        { T::RetrieveValueToEntity(statement, column_index, entity) } -> std::same_as<void>;
    };

}