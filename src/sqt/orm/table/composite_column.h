#pragma once

#include <array>
#include <sqt/orm/table/column.h>
#include <sqt/orm/table/column_type.h>
#include <sqt/orm/value/traits/trivial_value_traits.h>

namespace sqt {

template<ColumnType... Columns>
class CompositeColumn;


template<ColumnType First, ColumnType... Rest>
class CompositeColumn<First, Rest...> {
public:
    static_assert((std::is_same_v<typename First::EntityType, typename Rest::EntityType> && ...));

    using EntityType = typename First::EntityType;
    using ValueType = std::tuple<typename First::ValueType, typename Rest::ValueType...>;
    
    static constexpr std::size_t ColumnCount = 1 + sizeof...(Rest);

    static std::string BuildColumnNames() {
        std::string result{ First::Name };
        ((result.append(1, ',').append(Rest::Name)), ...);
        return result;
    }

    static void BindValueToStatement(
        Statement& statement,
        int parameter_index,
        const ValueType& value) {

        TrivialValueTraits<ValueType>::BindValueToStatement(statement, parameter_index, value);
    }

    static ValueType GetValueFromStatement(const Statement& statement, int column_index) {
        return TrivialValueTraits<ValueType>::GetValueFromStatement(statement, column_index);
    }

public:
    constexpr CompositeColumn(const First& first, const Rest&... rest) noexcept : 
        columns_({ &first, &rest... }) {

    }

    constexpr ColumnsView<EntityType> GetColumns() const noexcept {
        return columns_;
    }

    AbstractColumnsView GetAbstractColumns() const noexcept {
        return {
            reinterpret_cast<const AbstractColumn* const*>(columns_.data()),
            columns_.size()
        };
    }

private:
    std::array<const Column<EntityType>*, ColumnCount> columns_;
};


template<ColumnType Single>
class CompositeColumn<Single> {
public:
    using EntityType = typename Single::EntityType;
    using ValueType = typename Single::ValueType;

    static constexpr std::size_t ColumnCount = 1;

    static std::string BuildColumnNames() {
        return std::string{ Single::Name };
    }

    static void BindValueToStatement(
        Statement& statement,
        int parameter_index,
        const ValueType& value) {

        TrivialValueTraits<ValueType>::BindValueToStatement(statement, parameter_index, value);
    }

    static ValueType GetValueFromStatement(const Statement& statement, int column_index) {
        return TrivialValueTraits<ValueType>::GetValueFromStatement(statement, column_index);
    }

public:
    constexpr explicit CompositeColumn(const Single& single) noexcept : column_(&single) {

    }

    constexpr ColumnsView<EntityType> GetColumns() const noexcept {
        return ColumnsView<EntityType>{ &column_, 1 };
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


template<ColumnType... Columns>
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