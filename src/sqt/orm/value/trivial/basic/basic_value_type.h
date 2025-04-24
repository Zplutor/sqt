#pragma once

/**
@file
    Defines the `sqt::BasicValueType` concept.
*/

#include <sqt/orm/value/trivial/basic/custom_value_type.h>
#include <sqt/orm/value/trivial/basic/nullable_value_type.h>
#include <sqt/orm/value/trivial/basic/primitive_value_type.h>

namespace sqt {

/**
Constrains a type to be a basic value type, which can be used as the value type of fields or 
accessors bound to database columns.

@details
    @b Requirements
    - The type must satisfy one of the following concepts:
      - `sqt::PrimitiveValueType`
      - `sqt::NullableValueType`
      - `sqt::CustomValueType`

    When defining table columns using the `SQT_COLUMN_FIELD` or `SQT_COLUMN_ACCESSOR` macros, the 
    type of the field or accessor must satisfy this concept.

@see sqt::PrimitiveValueType
@see sqt::NullableValueType
@see sqt::CustomValueType
@see SQT_COLUMN_ACCESSOR
@see SQT_COLUMN_FIELD
*/
template<typename T>
concept BasicValueType = PrimitiveValueType<T> || NullableValueType<T> || CustomValueType<T>;

}