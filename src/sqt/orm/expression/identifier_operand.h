#pragma once

#include <sqt/foundation/statement.h>
#include <sqt/orm/expression/operand.h>
#include <sqt/orm/table/column_like.h>

namespace sqt {

class IdentifierOperand {
public:
    static constexpr std::size_t ParameterCount = 0;

    static constexpr std::tuple<> BuildPlaceholderBinders(int parameter_index) noexcept {
        return {};
    }

public:
    constexpr IdentifierOperand() noexcept = default;

    constexpr void BindInlineParameters(Statement& statement, int parameter_index) const noexcept {

    }
};


//Used for individual column.
template<ColumnLike T>
class Operand<T> : public IdentifierOperand {
public:
    using EntityType = typename T::EntityType;

    static std::string BuildSQL() {
        return std::string{ T::Name };
    }

public:
    constexpr explicit Operand(const T&) noexcept {

    }
};

}