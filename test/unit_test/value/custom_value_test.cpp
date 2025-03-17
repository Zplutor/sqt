#include <gtest/gtest.h>
#include <sqt/orm/value/trivial/basic/basic_value_traits_mapping.h>
#include <sqt/orm/value/trivial/basic/basic_value_traits_type.h>
#include <sqt/orm/value/trivial/basic/custom_value_traits.h>
#include <sqt/orm/value/trivial/basic/custom_value_type.h>
#include "unit_test/value/test_custom_value.h"

TEST(CustomValueTest, CustomValueType) {

    ASSERT_TRUE(sqt::CustomValueType<test_custom_value::BLOB>);
}


TEST(CustomValueTest, CustomValueTraits) {

    using ValueTraits = sqt::CustomValueTraits<test_custom_value::BLOB>;
    ASSERT_TRUE(sqt::BasicValueTraitsType<ValueTraits>);
    ASSERT_EQ(ValueTraits::DataType, sqt::DataType::BLOB);
    ASSERT_EQ(ValueTraits::IsNullable, false);
}


TEST(CustomValueTest, BasicValueTraitsMapping) {

    ASSERT_TRUE((std::is_same_v<
        sqt::BasicValueTraitsForT<test_custom_value::BLOB>,
        sqt::CustomValueTraits<test_custom_value::BLOB>>));
}