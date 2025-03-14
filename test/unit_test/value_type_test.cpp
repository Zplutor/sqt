#include <gtest/gtest.h>
#include <sqt/orm/value/composite_value_type.h>

using namespace sqt;

TEST(ValueTypeTest, CompositeValueType) {

    {
        using Type1 = std::tuple<int>;
        ASSERT_TRUE(CompositeValueType<Type1>);
    }

    {
        using Type2 = std::tuple<int, std::string>;
        ASSERT_TRUE(CompositeValueType<Type2>);
    }
}