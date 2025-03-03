#pragma once

#include <sqt/foundation/statement.h>
#include <sqt/orm/expression/operand/identifier_operand_type.h>
#include <sqt/orm/expression/ordering.h>

namespace sqt {

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