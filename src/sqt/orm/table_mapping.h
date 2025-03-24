#pragma once

/**
@file
    Defines the `sqt::TableMapping` primary template and related helper templates.
*/

namespace sqt {

/**
The primary template for mapping an entity type to its corresponding table type.

@tparam ENTITY 
    The entity type to map. 

@details
    `sqt::TableMapping` is a template intended to be specialized for each entity type. To enable 
    table mapping for a specific entity type, its table type should be registered using the 
    `SQT_REGISTER` macro.

    The `SQT_REGISTER` macro generates a partial specialization of `sqt::TableMapping` for the 
    specified entity type, defining a `type` alias that refers to the corresponding table type.

    There are two helper templates to access the table type and its instance:
    - `sqt::TableType<ENTITY>`: Retrieves the mapped table type.
    - `sqt::Table<ENTITY>`: Retrieves a reference to the singleton instance of the table.

@see SQT_REGISTER
@see sqt::TableType<>
@see sqt::Table<>
*/
template<typename ENTITY>
struct TableMapping;


/**
A helper template to retrieve the table type associated with an entity type.

@tparam ENTITY
    The entity type.

@details
    This template is a shorthand for `sqt::TableMapping<ENTITY>::type`.

@see sqt::TableMapping<>
*/
template<typename ENTITY>
using TableType = TableMapping<ENTITY>::type;


/**
A helper template to retrieve the singleton instance of the table type associated with an entity 
type.

@tparam ENTITY
    The entity type.

@details
    This template is a shorthand for `sqt::TableMapping<ENTITY>::type::GetInstance()`.

@see sqt::TableMapping<>
*/
template<typename ENTITY>
constexpr const auto& Table = TableType<ENTITY>::GetInstance();

}