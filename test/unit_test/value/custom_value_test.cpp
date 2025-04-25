#include <gtest/gtest.h>
#include <sqt/orm/value/trivial/basic/basic_value_traits_mapping.h>
#include <sqt/orm/value/trivial/basic/basic_value_traits_type.h>
#include <sqt/orm/value/trivial/basic/custom_value_traits.h>
#include <sqt/orm/value/trivial/basic/custom_value_type.h>
#include "unit_test/fixture/blob.h"

TEST(CustomValueTest, CustomValueType) {

    ASSERT_TRUE(sqt::CustomValueType<BLOB>);
}


TEST(CustomValueTest, CustomValueTraits) {

    using ValueTraits = sqt::CustomValueTraits<BLOB>;
    ASSERT_TRUE(sqt::BasicValueTraitsType<ValueTraits>);
    ASSERT_EQ(ValueTraits::DataType, sqt::DataType::BLOB);
    ASSERT_EQ(ValueTraits::IsNullable, false);
}


TEST(CustomValueTest, BasicValueTraitsMapping) {

    ASSERT_TRUE((std::is_same_v<
        sqt::BasicValueTraitsMappingT<BLOB>,
        sqt::CustomValueTraits<BLOB>>));
}