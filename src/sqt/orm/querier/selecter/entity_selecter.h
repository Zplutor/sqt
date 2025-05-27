#pragma once

/**
@file
    Defines the `sqt::EntitySelecter<>` class template.
*/

#include <sqt/orm/internal/utility.h>
#include <sqt/orm/querier/selecter/base_selecter.h>
#include <sqt/orm/table_mapping.h>
#include <sqt/orm/value/entity/entire_entity_value_traits.h>
#include <sqt/orm/value/entity/entity_value_type.h>

namespace sqt {

/**
A primary selecter that selects the entire entity from the table.

@tparam ENTITY
    The entity type that the selecter selects. It must satisfy the `sqt::EntityValueType` concept.

@details
    This class template defines a primary selecter that selects all columns from the table and 
    returns them as entity instances.

    To create an instance of this selecter, use the `sqt::DataContext::MakeSelecter()` method.

    This class template satisfies the `sqt::SelecterType` concept.
    
@see sqt::DataContext<>::MakeSelecter()
@see sqt::EntityValueType
@see sqt::SelecterType
*/
template<EntityValueType ENTITY>
class EntitySelecter : public BaseSelecter<EntitySelecter<ENTITY>> {
public:
    using EntityType = ENTITY;
    using ResultElementType = ENTITY;

    /**
    Retrieves an entity from the statement.

    @param statement
        The statement from which the entity is retrieved.

    @return
        An entity retrieved from the statement.

    @details
        This method delegates to the `RetrieveValue()` method of the
        `sqt::EntireEntityValueTraits<>`.

    @see sqt::EntireEntityValueTraits<>
    */
    static ResultElementType GetResultElement(Statement& statement) {
        return EntireEntityValueTraits<ENTITY>::RetrieveValue(statement, 0);
    }

public:
    constexpr EntitySelecter() noexcept = default;

private:
    friend class BaseSelecter<EntitySelecter<ENTITY>>;

    static std::string BuildColumnNames() {
        return internal::JoinColumnNames(EntireEntityValueTraits<ENTITY>::ManipulatingColumns);
    }
};

}