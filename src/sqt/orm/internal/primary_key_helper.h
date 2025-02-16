#pragma once

#include <sqt/orm/table/column.h>

namespace sqt::internal {

template<typename T>
concept HasPrimaryKey = requires (T t) {
    t.PrimaryKey;
};

template<typename T>
struct PrimaryKeyHelper {
    static constexpr ColumnsView<typename T::EntityType> GetPrimaryKeyColumns() {
        return {};
    }
};

template<HasPrimaryKey T>
struct PrimaryKeyHelper<T> {
    static constexpr ColumnsView<typename T::EntityType> GetPrimaryKeyColumns() {
        return T::GetInstance().PrimaryKey.GetColumns();
    }
};

}