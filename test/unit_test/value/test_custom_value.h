#pragma once

#include <vector>
#include <sqt/orm/value/trivial/basic/custom_value_traits.h>

namespace test_custom_value {
class BLOB {
public:
    std::vector<std::byte> data;
};
}

namespace sqt {

template<>
class CustomValueTraits<test_custom_value::BLOB> {
public:
    using ValueType = test_custom_value::BLOB;

    static constexpr sqt::DataType DataType = sqt::DataType::BLOB;
    static constexpr bool IsNullable = false;

    static void BindValue(
        sqt::Statement& statement,
        int parameter_index,
        const test_custom_value::BLOB& blob) {

        statement.BindParameter(parameter_index, blob.data);
    }

    static test_custom_value::BLOB RetrieveValue(
        const sqt::Statement& statement,
        int column_index) {

        auto blob = statement.GetColumnBLOB(column_index);
        test_custom_value::BLOB result;
        result.data.assign(blob.begin(), blob.end());
        return result;
    }
};

}