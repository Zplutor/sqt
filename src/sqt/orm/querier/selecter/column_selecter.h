#pragma once

#include <sqt/orm/querier/selecter/base_selecter.h>
#include <sqt/orm/table/column_type.h>
#include <sqt/orm/table/composite_column.h>
#include <sqt/orm/value/trivial_value_traits.h>

namespace sqt {

template<ColumnType... COLUMN>
class ColumnSelecter : public BaseSelecter<ColumnSelecter<COLUMN...>> {
public:
    using EntityType = typename std::tuple_element_t<0, std::tuple<COLUMN...>>::EntityType;
    using CompositeColumnType = CompositeColumn<COLUMN...>;
    using ResultElementType = typename CompositeColumnType::ValueType;

    static ResultElementType GetResultElement(Statement& statement) {
        return TrivialValueTraits<ResultElementType>::GetValueFromStatement(statement, 0);
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