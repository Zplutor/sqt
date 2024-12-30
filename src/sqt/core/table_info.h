#pragma once

#include <string>
#include <vector>
#include <sqt/core/data_type.h>

namespace sqt {

struct ColumnInfo {
    std::string name;
    DataType data_type{ DataType::Null };
    bool is_primary_key{};
    bool is_nullable{};
};

struct TableInfo {
    std::vector<ColumnInfo> columns;
};

}