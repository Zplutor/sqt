#pragma once

/**
@file 
    Defines the `sqt::OrderingTerm<>` class template.
*/

#include <sqt/foundation/statement.h>
#include <sqt/orm/expression/operand/identifier_operand_type.h>
#include <sqt/orm/expression/ordering.h>

namespace sqt {

/**
Represents an ordering term used in the `ORDER BY` clause.

@tparam ORDERING
    The ordering direction.

@tparam OPERAND
    The identifier operand type used to sort, which must satisfy the `sqt::IdentifierOperandType` 
    concept.

@details
    This class template satisfies the `sqt::OrderingTermType` concept.

@see sqt::IdentifierOperandType
@see sqt::Ordering
@see sqt::OrderingTermType
*/
template<Ordering ORDERING, IdentifierOperandType OPERAND>
class OrderingTerm {
public:
    static constexpr Ordering OrderingValue = ORDERING;

    static constexpr std::size_t ParameterCount = 0;

    static std::string BuildSQL() {

        std::string sql = OPERAND::BuildSQL();
        if (ORDERING == Ordering::Ascending) {
            sql += " asc";
        }
        else {
            sql += " desc";
        }
        return sql;
    }

    static constexpr auto BuildPlaceholderBinders(int parameter_index) noexcept {
        return std::tuple<>{};
    }

public:
    constexpr OrderingTerm() noexcept = default;

    void BindInlineParameters(Statement&, int) const noexcept {

    }
};

}