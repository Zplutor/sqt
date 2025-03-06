#pragma once

#include <sqt/orm/table/column_type.h>
#include <sqt/orm/table/composite_column_type.h>

namespace sqt {

template<typename T>
concept IdentifierType = ColumnType<T> || CompositeColumnType<T>;

}