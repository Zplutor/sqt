#pragma once

/**
@file
    Defines the `sqt::CustomValueTraits` primary template.
*/

#include <sqt/foundation/data_type.h>
#include <sqt/foundation/statement.h>

namespace sqt {

/**
The primary template for defining traits for custom value types.

@tparam T
    The custom value type for which to define traits.

@details
    This primary template is intended to be specialized by users for each custom value type.
    Specializing this template allows fields or accessors with custom value types to be used in 
    column definitions via the `SQT_COLUMN_FIELD` or `SQT_COLUMN_ACCESSOR` macros.
    
    Specializations must satisfy the `sqt::BasicValueTraitsType` concept. The following example
    demonstrates how to define a specialization for a custom value type mapped to the BLOB data 
    type:
    @code{.cpp}

    // The custom value type.
    struct BLOB {
        std::vector<std::byte> data;
    };

    // The specialization must be defined within the `sqt` namespace.
    namespace sqt {

    // The specialization for the BLOB type.
    template<>
    class CustomValueTraits<BLOB> {
    public:
        // This type alias must match the custom value type.
        using ValueType = BLOB;

        // Specifies the data type to which the custom value type is mapped.
        static constexpr sqt::DataType DataType = sqt::DataType::BLOB;

        // Indicates whether the custom value type is nullable.
        static constexpr bool IsNullable = false;

        // Binds the custom value to a statement parameter.
        static void BindValue(sqt::Statement& statement, int parameter_index, const BLOB& blob) {
            statement.BindParameter(parameter_index, blob.data);
        }

        // Retrieves the custom value from a statement column.
        static BLOB RetrieveValue(const sqt::Statement& statement, int column_index) {
            auto blob = statement.GetColumnBLOB(column_index);
            BLOB result;
            result.data.assign(blob.begin(), blob.end());
            return result;
        }
    };

    }
    @endcode

@see sqt::BasicValueTraitsType
@see SQT_COLUMN_ACCESSOR
@see SQT_COLUMN_FIELD
*/
template<typename T>
class CustomValueTraits;

}