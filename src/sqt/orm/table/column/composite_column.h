#pragma once

#include <array>
#include <sqt/orm/table/column/column.h>
#include <sqt/orm/table/column/column_type.h>
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
        using ValueType = ValueType;

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

}