#pragma once

#include <span>
#include <sqt/core/statement.h>
#include <sqt/orm/abstract_column.h>

namespace sqt {

template<typename E>
class Column : public AbstractColumn {
public:
    constexpr Column() noexcept = default;

    virtual void BindValueToStatement(
        Statement& statement,
        int parameter_index,
        const E& entity) const = 0;

    virtual void GetValueFromStatement(
        const Statement& statement,
        int index,
        E& entity) const = 0;
};


template<typename E>
using ColumnsView = std::span<const Column<E>* const>;


template<typename T, typename = void>
struct IsColumn : std::false_type {};

template<typename T>
struct IsColumn<T, std::enable_if_t<std::is_base_of_v<AbstractColumn, T>>> : std::true_type {};

template<typename T>
constexpr bool IsColumnV = IsColumn<T>::value;

}