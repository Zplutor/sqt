#pragma once

#include <array>
#include <sqt/orm/table/column.h>
#include <sqt/orm/table/column_like.h>
#include <sqt/orm/value_type/composite_value_type.h>

namespace sqt {

template<ColumnLike... Columns>
class CompositeColumn;


template<ColumnLike First, ColumnLike... Rest>
class CompositeColumn<First, Rest...> {
public:
    static_assert((std::is_same_v<typename First::EntityType, typename Rest::EntityType> && ...));

    using EntityType = typename First::EntityType;
    using ValueType = std::tuple<typename First::ValueType, typename Rest::ValueType...>;

    static void BindValueToStatement(
        Statement& statement,
        int parameter_index,
        const ValueType& value) {

        ValueTypeTraits<ValueType>::BindValueToStatement(statement, parameter_index, value);
    }

    static ValueType GetValueFromStatement(const Statement& statement, int column_index) {
        return ValueTypeTraits<ValueType>::GetValueFromStatement(statement, column_index);
    }

public:
    constexpr CompositeColumn(const First& first, const Rest&... rest) noexcept : 
        columns_({ &first, &rest... }) {

    }

    AbstractColumnsView GetAbstractColumns() const noexcept {
        return {
            reinterpret_cast<const AbstractColumn* const*>(columns_.data()),
            columns_.size()
        };
    }

private:
    std::array<const Column<EntityType>*, 1 + sizeof...(Rest)> columns_;
};


template<ColumnLike Single>
class CompositeColumn<Single> {
public:
    using EntityType = typename Single::EntityType;
    using ValueType = typename Single::ValueType;

    static void BindValueToStatement(
        Statement& statement,
        int parameter_index,
        const ValueType& value) {

        ValueTypeTraits<ValueType>::BindValueToStatement(statement, parameter_index, value);
    }

    static ValueType GetValueFromStatement(const Statement& statement, int column_index) {
        return ValueTypeTraits<ValueType>::GetValueFromStatement(statement, column_index);
    }

public:
    constexpr explicit CompositeColumn(const Single& single) noexcept : column_(&single) {

    }

    AbstractColumnsView GetAbstractColumns() const noexcept {
        return AbstractColumnsView{ 
            reinterpret_cast<const AbstractColumn* const*>(&column_), 
            1
        };
    }

private:
    const Column<EntityType>* column_{};
};


template<ColumnLike... Columns>
constexpr auto MakeCompositeColumn(const Columns&... columns) { 
    return CompositeColumn<Columns...>{ columns... };
}


template<typename T>
struct IsCompositeColumnBased {
private:
    template<typename K, typename E, typename... Columns>
    static constexpr bool Test(CompositeColumn<E, Columns...>*) {
        return true;
    }

    template<typename K>
    static constexpr bool Test(...) {
        return false;
    }

public:
    static constexpr bool value = Test<T>((T*)nullptr);
};

template<typename T>
constexpr bool IsCompositeColumnBasedV = IsCompositeColumnBased<T>::value;

}