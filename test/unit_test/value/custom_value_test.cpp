#include <gtest/gtest.h>
#include <sqt/orm/value/trivial/basic/basic_value_traits_mapping.h>
#include <sqt/orm/value/trivial/basic/basic_value_traits_type.h>
#include <sqt/orm/value/trivial/basic/custom_value_traits.h>
#include <sqt/orm/value/trivial/basic/custom_value_type.h>

namespace custom_value_test {
class BLOB {
public:
    std::vector<std::byte> data;
};
}

namespace sqt {

template<>
class CustomValueTraits<custom_value_test::BLOB> {
public:
    using ValueType = custom_value_test::BLOB;

    static constexpr sqt::DataType DataType = sqt::DataType::BLOB;
    static constexpr bool IsNullable = false;

    static void BindValue(
        sqt::Statement& statement, 
        int parameter_index, 
        const custom_value_test::BLOB& blob) {

        statement.BindParameter(parameter_index, blob.data);
    }

    static custom_value_test::BLOB RetrieveValue(
        const sqt::Statement& statement, 
        int column_index) {

        auto blob = statement.GetColumnBLOB(column_index);
        custom_value_test::BLOB result;
        result.data.assign(blob.begin(), blob.end());
        return result;
    }
};

}


TEST(CustomValueTest, CustomValueType) {

    ASSERT_TRUE(sqt::CustomValueType<custom_value_test::BLOB>);
}


TEST(CustomValueTest, CustomValueTraits) {

    using ValueTraits = sqt::CustomValueTraits<custom_value_test::BLOB>;
    ASSERT_TRUE(sqt::BasicValueTraitsType<ValueTraits>);
    ASSERT_EQ(ValueTraits::DataType, sqt::DataType::BLOB);
    ASSERT_EQ(ValueTraits::IsNullable, false);
}


TEST(CustomValueTest, BasicValueTraitsMapping) {

    ASSERT_TRUE((std::is_same_v<
        sqt::BasicValueTraitsForT<custom_value_test::BLOB>,
        sqt::CustomValueTraits<custom_value_test::BLOB>>));
}