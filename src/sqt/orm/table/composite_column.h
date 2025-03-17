#pragma once

#include <array>
#include <sqt/orm/table/column.h>
#include <sqt/orm/table/column_type.h>
#include <sqt/orm/value/trivial/composite/composite_value_traits.h>

namespace sqt {

template<ColumnType... Columns>
class CompositeColumn;


template<ColumnType FIRST, ColumnType... REST>
class CompositeColumn<FIRST, REST...> {
public:
    static_assert((std::is_same_v<typename FIRST::EntityType, typename REST::EntityType> && ...));

    using EntityType = typename FIRST::EntityType;

    using ValueTraits = CompositeValueTraits<
        typename FIRST::ValueTraits, 
        typename REST::ValueTraits...
    >;

    using ValueType = typename ValueTraits::ValueType;

    class ValueSource {
    public:
        static ValueType GetValueFromEntity(const EntityType& entity) {
            return ValueType{
                FIRST::ValueSource::GetValueFromEntity(entity),
                REST::ValueSource::GetValueFromEntity(entity)...
            };
        }

        static void SetValueToEntity(EntityType& entity, ValueType&& value) {
            std::apply(
                [&entity](auto&&... values) {
                    FIRST::ValueSource::SetValueToEntity(entity, std::move(values));
                    (REST::ValueSource::SetValueToEntity(entity, std::move(values)), ...);
                },
                std::move(value));
        }
    };

    static constexpr std::size_t ColumnCount = 1 + sizeof...(REST);

    static std::string BuildColumnNames() {
        std::string result{ FIRST::Name };
        ((result.append(1, ',').append(REST::Name)), ...);
        return result;
    }

    static void BindValueFromEntity(
        Statement& statement, 
        int parameter_index, 
        const EntityType& entity) {

        FIRST::BindValueFromEntity(statement, parameter_index, entity);

        int index = parameter_index + 1;
        ((REST::BindValueFromEntity(statement, index++, entity)), ...);
    }

    static void RetrieveValueToEntity(
        const Statement& statement,
        int column_index,
        EntityType& entity) {

        FIRST::RetrieveValueToEntity(statement, column_index, entity);

        int index = column_index + 1;
        ((REST::RetrieveValueToEntity(statement, index++, entity)), ...);
    }

public:
    constexpr CompositeColumn(const FIRST& first, const REST&... rest) noexcept : 
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
    using ValueTraits = typename Single::ValueTraits;
    using ValueType = typename Single::ValueType;
    using ValueSource = typename Single::ValueSource;

    static constexpr std::size_t ColumnCount = 1;

    static std::string BuildColumnNames() {
        return std::string{ Single::Name };
    }

    static void BindValueFromEntity(
        Statement& statement,
        int parameter_index,
        const EntityType& entity) {

        Single::BindValueFromEntity(statement, parameter_index, entity);
    }

    static void RetrieveValueToEntity(
        const Statement& statement,
        int column_index,
        EntityType& entity) {

        Single::RetrieveValueToEntity(statement, column_index, entity);
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