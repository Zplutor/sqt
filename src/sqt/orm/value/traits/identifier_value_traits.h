#pragma once

#include <sqt/foundation/statement.h>
#include <sqt/orm/table/identifier_type.h>

namespace sqt {

template<IdentifierType IDENTIFIER>
class IdentifierValueTraits {
public:
    using IdentifierType = IDENTIFIER;
    using EntityType = typename IDENTIFIER::EntityType;
    using ValueType = typename IDENTIFIER::ValueType;

    static constexpr std::size_t ParameterCount = IDENTIFIER::ValueTraits::ParameterCount;

    static void BindValue(Statement& statement, int parameter_index, const ValueType& value) {
        IDENTIFIER::ValueTraits::BindValue(statement, parameter_index, value);
    }

    static void BindValueFromEntity(
        Statement& statement, 
        int parameter_index, 
        const EntityType& entity) {

    }

    static ValueType RetrieveValue(const Statement& statement, int column_index) {
        return IDENTIFIER::ValueTraits::RetrieveValue(statement, column_index);
    }

    static void RetrieveValueToEntity(
        const Statement& statement, 
        int column_index,
        EntityType& entity) {

    }
};

}