#include <gtest/gtest.h>
#include <sqt/orm/value/composite_value_type.h>
#include <sqt/orm/value/nullable_value_type.h>
#include <sqt/orm/value/primitive_value_type.h>

using namespace sqt;

TEST(ValueTypeTest, NullableValueType) {

    ASSERT_TRUE(NullableValueType<std::optional<bool>>);

    ASSERT_TRUE(NullableValueType<std::optional<char>>);
    ASSERT_TRUE(NullableValueType<std::optional<signed char>>);
    ASSERT_TRUE(NullableValueType<std::optional<unsigned char>>);
    ASSERT_TRUE(NullableValueType<std::optional<char8_t>>);
    ASSERT_TRUE(NullableValueType<std::optional<char16_t>>);
    ASSERT_TRUE(NullableValueType<std::optional<char32_t>>);
    ASSERT_TRUE(NullableValueType<std::optional<wchar_t>>);

    ASSERT_TRUE(NullableValueType<std::optional<short>>);
    ASSERT_TRUE(NullableValueType<std::optional<unsigned short>>);
    ASSERT_TRUE(NullableValueType<std::optional<int>>);
    ASSERT_TRUE(NullableValueType<std::optional<unsigned int>>);
    ASSERT_TRUE(NullableValueType<std::optional<long>>);
    ASSERT_TRUE(NullableValueType<std::optional<unsigned long>>);
    ASSERT_TRUE(NullableValueType<std::optional<long long>>);
    ASSERT_TRUE(NullableValueType<std::optional<unsigned long long>>);

    ASSERT_TRUE(NullableValueType<std::optional<float>>);
    ASSERT_TRUE(NullableValueType<std::optional<double>>);
    ASSERT_TRUE(NullableValueType<std::optional<long double>>);

    ASSERT_TRUE(NullableValueType<std::optional<std::string>>);
}


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