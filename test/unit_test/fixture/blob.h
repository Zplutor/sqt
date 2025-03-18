#pragma once

#include <vector>
#include <sqt/orm/value/trivial/basic/custom_value_traits.h>

class BLOB {
public:
    std::vector<std::byte> data;
};

namespace sqt {

template<>
class CustomValueTraits<BLOB> {
public:
    using ValueType = BLOB;

    static constexpr sqt::DataType DataType = sqt::DataType::BLOB;
    static constexpr bool IsNullable = false;

    static void BindValue(sqt::Statement& statement, int parameter_index, const BLOB& blob) {
        statement.BindParameter(parameter_index, blob.data);
    }

    static BLOB RetrieveValue(const sqt::Statement& statement, int column_index) {
        auto blob = statement.GetColumnBLOB(column_index);
        BLOB result;
        result.data.assign(blob.begin(), blob.end());
        return result;
    }
};

}