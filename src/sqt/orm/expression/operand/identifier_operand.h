#pragma once

#include <sqt/foundation/statement.h>
#include <sqt/orm/table/column_type.h>
#include <sqt/orm/table/composite_column_type.h>

namespace sqt {

template<typename T>
class BaseIdentifierOperand {
public:
    using IdentifierType = T;
    using EntityType = typename T::Descriptor::EntityType;

    static constexpr std::size_t ParameterCount = 0;

    static constexpr std::tuple<> BuildPlaceholderBinders(int parameter_index) noexcept {
        return {};
    }

public:
    constexpr void BindInlineParameters(Statement& statement, int parameter_index) const noexcept {

    }

protected:
    constexpr BaseIdentifierOperand() noexcept = default;
};


template<typename T>
class IdentifierOperand;


template<ColumnType T>
class IdentifierOperand<T> : public BaseIdentifierOperand<T> {
public:
    static std::string BuildSQL() {
        return std::string{ T::Name };
    }

public:
    constexpr IdentifierOperand() noexcept = default;
};


template<CompositeColumnType T>
class IdentifierOperand<T> : public BaseIdentifierOperand<T> {
public:
    static std::string BuildSQL() {
        return T::BuildColumnNames();
    }

public:
    constexpr IdentifierOperand() noexcept = default;
};

}