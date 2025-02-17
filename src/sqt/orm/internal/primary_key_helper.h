#pragma once

#include <sqt/orm/table/column.h>

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
};


template<HasPrimaryKey T>
struct PrimaryKeyShim<T> {

    static constexpr std::size_t PKColumnCount = T::PrimaryKeyType::ColumnCount;

    static constexpr ColumnsView<typename T::EntityType> GetPKColumns(const T& table) noexcept {
        return table.PrimaryKey.GetColumns();
    }
};


template<typename T>
struct PrimaryKeyHelper {
private:
    using EntityType = typename T::EntityType;

public:
    template<std::size_t Count>
    static constexpr std::array<const Column<EntityType>*, Count> MakeNonPKColumns(
        ColumnsView<EntityType> all_columns,
        ColumnsView<EntityType> pk_columns) noexcept {

        if (Count == 0) {
            return {};
        }

        std::array<const Column<EntityType>*, Count> result;
        std::size_t index{};
        for (auto each_column : all_columns) {

            bool is_pk{};
            for (auto each_pk_column : pk_columns) {
                if (each_column == each_pk_column) {
                    is_pk = true;
                    break;
                }
            }
            if (is_pk) {
                continue;
            }

            if (index < Count) {
                result[index++] = each_column;
            }
        }

        return result;
    }
};

}