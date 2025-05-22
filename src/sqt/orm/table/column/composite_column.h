#pragma once

/**
@file
    Defines the `sqt::CompositeColumn<>` primary template and its specialization for various 
    numbers of columns.
*/

#include <array>
#include <sqt/orm/internal/column_array.h>
#include <sqt/orm/table/column/column.h>
#include <sqt/orm/table/column/column_type.h>
#include <sqt/orm/value/trivial/composite/composite_value_traits.h>

namespace sqt {

/**
The primary template for defining composite column types for various number of columns.

@tparam COLUMNS
    The column types that compose the composite column. They must satisfy the `sqt::ColumnType` 
    concept.

@details
    Depending on the number of columns, there are two specializations of this template:
    - `sqt::CompositeColumn<FIRST, REST...>`: This specialization is used when there are multiple
      columns.
    - `sqt::CompositeColumn<SINGLE>`: This specialization is used when there is only one column.

    They both satisfy the `sqt::CompositeColumnType` concept.

@see sqt::CompositeColumn<FIRST, REST...>
@see sqt::CompositeColumn<SINGLE>
@see sqt::CompositeColumnType
*/
template<ColumnType... COLUMNS>
class CompositeColumn;


/**
The specialization of the `sqt::CompositeColumn<>` template for multiple columns.

@tparam FIRST
    The first column type in the composite column.

@tparam REST
    The remaining column types in the composite column. Their nested type `EntityType` must be the
    same as the `EntityType` of the first column.

@details
    This specialization is used when there are multiple columns in the composite column. 

    This specialization satisfies the `sqt::CompositeColumnType` concept.

@see sqt::CompositeColumn<>
@see sqt::CompositeColumn<SINGLE>
@see sqt::CompositeColumnType
*/
template<ColumnType FIRST, ColumnType... REST>
class CompositeColumn<FIRST, REST...> {
public:
    static_assert((std::is_same_v<typename FIRST::EntityType, typename REST::EntityType> && ...));

    /**
    The entity type of the composite column.

    @details
        This type is the same as the `EntityType` of the first column.
    */
    using EntityType = typename FIRST::EntityType;

    /**
    The value traits of the composite column.

    @details
        This value traits is defined as a `sqt::CompositeValueTraits<>` that combines the value 
        traits of the first column and each of the remaining columns.

    @see sqt::CompositeValueTraits<>

    @showinitializer
    */
    using ValueTraits = CompositeValueTraits<
        typename FIRST::ValueTraits, 
        typename REST::ValueTraits...>;

    /**
    The value type of the composite columns.

    @details
        This type is defined as the same as the `ValueType` of the `sqt::CompositeValueTraits<>` 
        type, which is a `std::tuple<>` of the value types of the first column and each of the
        remaining columns.

    @see sqt::CompositeValueTraits<>
    */
    using ValueType = typename ValueTraits::ValueType;

    /**
    The value source of the composite column, which is used to retrieve and set composite values in
    the entity.

    @details
        This class satisfies the `sqt::ValueSourceType` concept.

    @see sqt::ValueSourceType
    */
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

    /**
    The collection of column types that compose the composite column.
    */
    using ColumnTypes = std::tuple<FIRST, REST...>;

    /**
    The number of columns in the composite column.
    */
    static constexpr std::size_t ColumnCount = std::tuple_size_v<ColumnTypes>;

    /**
    Create a string containing the names of all columns in the composite column.

    @return
        A string containing all column names, which are delimited by commas.
    */
    static std::string BuildColumnNames() {
        std::string result{ FIRST::Name };
        ((result.append(1, ',').append(REST::Name)), ...);
        return result;
    }

public:
    constexpr CompositeColumn() noexcept = default;

    /**
    Retrieves a view to all columns in the composite column.

    @return
        A view to columns.

    @see sqt::ColumnsView<>
    */
    constexpr ColumnsView<EntityType> GetColumns() const noexcept {
        return internal::ColumnArray<FIRST, REST...>::Columns;
    }

    /**
    Retrieves an abstract view to all columns in the composite column.

    @return
        An abstract view to columns.

    @see sqt::AbstractColumnsView
    */
    AbstractColumnsView GetAbstractColumns() const noexcept {
        auto columns = GetColumns();
        return {
            reinterpret_cast<const AbstractColumn* const*>(columns.data()),
            columns.size()
        };
    }
};


/**
The specialization of the `sqt::CompositeColumn<>` template for a single column.

@tparam SINGLE
    The single column type in the composite column.

@details
    This specialization is used when there is only one column in the composite column. Unlike the 
    other specialization, this specialization is merely an adaptor for the single column to satisfy
    the `sqt::CompositeColumnType` concept. Most of the nested types are defined as the same as the
    corresponding types in the single column.

@see sqt::CompositeColumn<>
@see sqt::CompositeColumn<FIRST, REST...>
*/
template<ColumnType SINGLE>
class CompositeColumn<SINGLE> {
public:
    using EntityType = typename SINGLE::EntityType;
    using ValueTraits = typename SINGLE::ValueTraits;
    using ValueType = typename SINGLE::ValueType;
    using ValueSource = typename SINGLE::ValueSource;
    using ColumnTypes = std::tuple<SINGLE>;

    static constexpr std::size_t ColumnCount = std::tuple_size_v<ColumnTypes>;

    /**
    Creates a string containing the name of the single column.

    @return
        A string containing the name of the single column. No extra delimiters are added.
    */
    static std::string BuildColumnNames() {
        return std::string{ SINGLE::Name };
    }

public:
    constexpr CompositeColumn() noexcept = default;

    /**
    Retrieves a view to the single column.

    @return
        A view to the single column.

    @see sqt::ColumnsView<>
    */
    constexpr ColumnsView<EntityType> GetColumns() const noexcept {
        return internal::ColumnArray<SINGLE>::Columns;
    }

    /**
    Retrieves an abstract view to the single column.

    @return
        An abstract view to the single column.

    @see sqt::AbstractColumnsView
    */
    AbstractColumnsView GetAbstractColumns() const noexcept {
        auto columns = GetColumns();
        return {
            reinterpret_cast<const AbstractColumn* const*>(columns.data()),
            columns.size()
        };
    }
};


/**
Creates a composite column from the specified columns.

@tparam COLUMNS
    The column types that compose the composite column.

@param columns
    The column instances. They are used to deduce the column types and will not be used.

@return
    The composite column instance.

@see sqt::CompositeColumn<>
*/
template<ColumnType... COLUMNS>
constexpr CompositeColumn<COLUMNS...> MakeCompositeColumn(const COLUMNS&... columns) noexcept {
    return CompositeColumn<COLUMNS...>{};
}

}