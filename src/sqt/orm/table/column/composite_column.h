#pragma once

#include <array>
#include <sqt/orm/internal/column_array.h>
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
    constexpr CompositeColumn() noexcept = default;

    constexpr ColumnsView<EntityType> GetColumns() const noexcept {
        return internal::ColumnArray<FIRST, REST...>::Columns;
    }

    AbstractColumnsView GetAbstractColumns() const noexcept {
        auto columns = GetColumns();
        return {
            reinterpret_cast<const AbstractColumn* const*>(columns.data()),
            columns.size()
        };
    }
};


template<ColumnType SINGLE>
class CompositeColumn<SINGLE> {
public:
    using EntityType = typename SINGLE::EntityType;
    using ValueTraits = typename SINGLE::ValueTraits;
    using ValueType = typename SINGLE::ValueType;
    using ValueSource = typename SINGLE::ValueSource;

    static constexpr std::size_t ColumnCount = 1;

    static std::string BuildColumnNames() {
        return std::string{ SINGLE::Name };
    }

public:
    constexpr CompositeColumn() noexcept = default;

    constexpr ColumnsView<EntityType> GetColumns() const noexcept {
        return internal::ColumnArray<SINGLE>::Columns;
    }

    AbstractColumnsView GetAbstractColumns() const noexcept {
        auto columns = GetColumns();
        return {
            reinterpret_cast<const AbstractColumn* const*>(columns.data()),
            columns.size()
        };
    }
};

}