#pragma once

/**
@file
    Defines the `sqt::ColumnSelecter<>` class template.
*/

#include <sqt/orm/querier/selecter/base_selecter.h>
#include <sqt/orm/table/column/column_type.h>
#include <sqt/orm/table/column/composite_column.h>

namespace sqt {

/**
A primary selecter that selects specific columns from the table.

@tparam COLUMNS...
    The column types to be selected. Each column type must satisfy the `sqt::ColumnType` concept.

@details
    This primary selecter selects specific columns from the table without any clauses and returns 
    them as a composite value type (a `std::tuple<>` of the selected columns' value types).

    To create instances of this selecter, use the 
    `sqt::DataContext::MakeSelecter(const COLUMNS&...)` method.

    This class template satisfies the `sqt::SelecterType` concept.

@see sqt::ColumnType
@see sqt::DataContext<>::MakeSelecter(const COLUMNS&... columns);
@see sqt::SelecterType
*/
template<ColumnType... COLUMNS>
class ColumnSelecter : public BaseSelecter<ColumnSelecter<COLUMNS...>> {
public:
    using CompositeColumnType = CompositeColumn<COLUMNS...>;
    using ColumnsValueTraits = typename CompositeColumnType::ValueTraits;

    using EntityType = typename CompositeColumnType::EntityType;
    using ResultElementType = typename ColumnsValueTraits::ValueType;

    /**
    Retrieves a composite value of the selected columns from the statement.

    @param statement
        The statement from which the composite value is retrieved.

    @return
        A `std::tuple<>` containing the values of the selected columns.

    @details
        This methods delegates to the `RetrieveValue()` method of the `sqt::CompositeValueTraits<>` 
        class template.

    @see sqt::CompositeValueTraits<>
    */
    static ResultElementType GetResultElement(Statement& statement) {
        return ColumnsValueTraits::RetrieveValue(statement, 0);
    }

public:
    constexpr ColumnSelecter() noexcept = default;

private:
    friend class BaseSelecter<ColumnSelecter<COLUMNS...>>;

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
        (append_name(COLUMNS::Name), ...);

        return result;
    }
};

}