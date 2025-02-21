#pragma once

#include <sqt/foundation/statement.h>
#include <sqt/orm/table/column_like.h>

namespace sqt {

template<ColumnLike T>
class IdentifierOperand {
public:
    using EntityType = typename T::EntityType;

    static constexpr std::size_t ParameterCount = 0;

    static std::string BuildSQL() {
        return std::string{ T::Name };
    }

    static constexpr std::tuple<> BuildPlaceholderBinders(int parameter_index) noexcept {
        return {};
    }

public:
    constexpr IdentifierOperand() noexcept = default;

    constexpr void BindInlineParameters(Statement& statement, int parameter_index) const noexcept {

    }
};

}