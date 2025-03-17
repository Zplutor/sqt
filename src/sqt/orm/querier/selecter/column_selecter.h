#pragma once

#include <sqt/orm/querier/selecter/base_selecter.h>
#include <sqt/orm/table/column/column_type.h>
#include <sqt/orm/table/column/composite_column.h>

namespace sqt {

template<ColumnType... COLUMN>
class ColumnSelecter : public BaseSelecter<ColumnSelecter<COLUMN...>> {
public:
    using CompositeColumnType = CompositeColumn<COLUMN...>;
    using ColumnsValueTraits = typename CompositeColumnType::ValueTraits;

    using EntityType = typename CompositeColumnType::EntityType;
    using ResultElementType = typename ColumnsValueTraits::ValueType;

    static ResultElementType GetResultElement(Statement& statement) {
        return ColumnsValueTraits::RetrieveValue(statement, 0);
    }

public:
    constexpr ColumnSelecter() noexcept = default;

private:
    friend class BaseSelecter<ColumnSelecter<COLUMN...>>;

    static std::string BuildColumnNames() {

        std::string result;
        int index{};
        const auto append_name = [&result, &index](std::string_view name) {
            if (index != 0) {
                result += ',';
            }
            result += name;
            index++;
        };
        (append_name(COLUMN::Name), ...);

        return result;
    }
};

}