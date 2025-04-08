#pragma once

#include <sqt/orm/table/column/column.h>
#include <sqt/foundation/statement.h>

namespace sqt::internal {

template<typename ENTITY>
void BindColumnValuesFromEntity(
    Statement& statement, 
    int parameter_index, 
    const ENTITY& value,
    sqt::ColumnsView<ENTITY> columns) {

    int index = parameter_index;
    for (auto each_column : columns) {
        each_column->BindValueFromEntity(statement, index++, value);
    }
}


template<typename ENTITY>
ENTITY RetrieveColumnValuesToEntity(
    const Statement& statement, 
    int column_index,
    sqt::ColumnsView<ENTITY> columns) {

    ENTITY result{};
    int index = column_index;
    for (auto each_column : columns) {
        each_column->RetrieveValueToEntity(statement, index++, result);
    }
    return result;
}

}