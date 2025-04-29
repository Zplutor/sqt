#pragma once

#include <sqt/orm/table/column/column.h>

namespace sqt::internal {

template<typename T>
concept HasPrimaryKey = requires (T t) {
    t.PrimaryKey;
};

template<typename T>
struct PrimaryKeyShim {

    static constexpr std::size_t PKColumnCount = 0;

    static constexpr ColumnsView<typename T::EntityType> GetPKColumns(const T& table) noexcept {
        return {};
    }

    static constexpr std::span<const std::size_t> GetPKColumnIndexes(const T& table) noexcept {
        return {};
    }
};


template<HasPrimaryKey T>
struct PrimaryKeyShim<T> {

    static constexpr std::size_t PKColumnCount = T::PrimaryKeyType::ColumnCount;

    static constexpr ColumnsView<typename T::EntityType> GetPKColumns(const T& table) noexcept {
        return table.PrimaryKey.GetColumns();
    }

    template<std::size_t INDEX>
    static constexpr std::size_t GetColumnIndex(const T& table) noexcept {

        using ColumnType = std::tuple_element_t<INDEX, typename T::PrimaryKeyType::ColumnTypes>;
        auto column = table.template GetColumn<ColumnType>();
        return static_cast<const ColumnType*>(column)->GetIndex();
    }

    template<std::size_t... INDEXES>
    static constexpr auto BuildColumnIndexes(
        const T& table, 
        std::index_sequence<INDEXES...>) noexcept {

        std::array<std::size_t, sizeof...(INDEXES)> indexes{};
        ((indexes[INDEXES] = GetColumnIndex<INDEXES>(table)), ...);
        return indexes;
    }

    static constexpr auto GetPKColumnIndexes(const T& table) noexcept {
        return BuildColumnIndexes(table, std::make_index_sequence<PKColumnCount>{});
    }
};


template<typename T>
struct PrimaryKeyHelper {
private:
    using EntityType = typename T::EntityType;

public:
    template<typename COLUMN_LINKED_LIST, std::size_t COUNT>
    static constexpr std::array<const Column<EntityType>*, COUNT> MakeNonPKColumns(
        const COLUMN_LINKED_LIST& column_linked_list,
        std::span<const std::size_t> pk_column_indexes) noexcept {

        if (COUNT == 0) {
            return {};
        }

        std::array<const Column<EntityType>*, COUNT> result{};
        std::size_t index{};

        for (auto current = column_linked_list.Last(); current; current = current->GetPrevious()) {

            bool is_pk{};
            for (auto pk_index : pk_column_indexes) {
                if (current->GetIndex() == pk_index) {
                    is_pk = true;
                    break;
                }
            }
            if (is_pk) {
                continue;
            }

            if (index < COUNT) {
                result[COUNT - index++ - 1] = static_cast<const Column<EntityType>*>(current);
            }
        }

        return result;
    }
};

}