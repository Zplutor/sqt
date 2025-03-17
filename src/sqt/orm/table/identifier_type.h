#pragma once

#include <sqt/orm/table/column/column_type.h>
#include <sqt/orm/table/column/composite_column_type.h>

namespace sqt {

template<typename T>
concept IdentifierType = ColumnType<T> || CompositeColumnType<T>;

}