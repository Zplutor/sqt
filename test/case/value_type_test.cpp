#include <gtest/gtest.h>
#include <sqt/orm/value_type/composite_value_type.h>

using namespace sqt;

TEST(ValueTypeTest, MapToDataType) {

    ASSERT_EQ(MapToDataTypeV<bool>, DataType::Integer);

    ASSERT_EQ(MapToDataTypeV<char>, DataType::Integer);
    ASSERT_EQ(MapToDataTypeV<signed char>, DataType::Integer);
    ASSERT_EQ(MapToDataTypeV<unsigned char>, DataType::Integer);
    ASSERT_EQ(MapToDataTypeV<char8_t>, DataType::Integer);
    ASSERT_EQ(MapToDataTypeV<char16_t>, DataType::Integer);
    ASSERT_EQ(MapToDataTypeV<char32_t>, DataType::Integer);
    ASSERT_EQ(MapToDataTypeV<wchar_t>, DataType::Integer);

    ASSERT_EQ(MapToDataTypeV<short>, DataType::Integer);
    ASSERT_EQ(MapToDataTypeV<unsigned short>, DataType::Integer);
    ASSERT_EQ(MapToDataTypeV<int>, DataType::Integer);
    ASSERT_EQ(MapToDataTypeV<unsigned int>, DataType::Integer);
    ASSERT_EQ(MapToDataTypeV<long>, DataType::Integer);
    ASSERT_EQ(MapToDataTypeV<unsigned long>, DataType::Integer);
    ASSERT_EQ(MapToDataTypeV<long long>, DataType::Integer);
    ASSERT_EQ(MapToDataTypeV<unsigned long long>, DataType::Integer);

    ASSERT_EQ(MapToDataTypeV<float>, DataType::Float);
    ASSERT_EQ(MapToDataTypeV<double>, DataType::Float);
    ASSERT_EQ(MapToDataTypeV<long double>, DataType::Float);

    ASSERT_EQ(MapToDataTypeV<std::string>, DataType::Text);
}


TEST(ValueTypeTest, PrimitiveValueLike) {

    ASSERT_TRUE(PrimitiveValueLike<bool>);

    ASSERT_TRUE(PrimitiveValueLike<char>);
    ASSERT_TRUE(PrimitiveValueLike<signed char>);
    ASSERT_TRUE(PrimitiveValueLike<unsigned char>);
    ASSERT_TRUE(PrimitiveValueLike<char8_t>);
    ASSERT_TRUE(PrimitiveValueLike<char16_t>);
    ASSERT_TRUE(PrimitiveValueLike<char32_t>);
    ASSERT_TRUE(PrimitiveValueLike<wchar_t>);

    ASSERT_TRUE(PrimitiveValueLike<short>);
    ASSERT_TRUE(PrimitiveValueLike<unsigned short>);
    ASSERT_TRUE(PrimitiveValueLike<int>);
    ASSERT_TRUE(PrimitiveValueLike<unsigned int>);
    ASSERT_TRUE(PrimitiveValueLike<long>);
    ASSERT_TRUE(PrimitiveValueLike<unsigned long>);
    ASSERT_TRUE(PrimitiveValueLike<long long>);
    ASSERT_TRUE(PrimitiveValueLike<unsigned long long>);

    ASSERT_TRUE(PrimitiveValueLike<float>);
    ASSERT_TRUE(PrimitiveValueLike<double>);
    ASSERT_TRUE(PrimitiveValueLike<long double>);

    ASSERT_TRUE(PrimitiveValueLike<std::string>);
}


TEST(ValueTypeTest, NullableValueLike) {

    ASSERT_TRUE(NullableValueLike<std::optional<bool>>);

    ASSERT_TRUE(NullableValueLike<std::optional<char>>);
    ASSERT_TRUE(NullableValueLike<std::optional<signed char>>);
    ASSERT_TRUE(NullableValueLike<std::optional<unsigned char>>);
    ASSERT_TRUE(NullableValueLike<std::optional<char8_t>>);
    ASSERT_TRUE(NullableValueLike<std::optional<char16_t>>);
    ASSERT_TRUE(NullableValueLike<std::optional<char32_t>>);
    ASSERT_TRUE(NullableValueLike<std::optional<wchar_t>>);

    ASSERT_TRUE(NullableValueLike<std::optional<short>>);
    ASSERT_TRUE(NullableValueLike<std::optional<unsigned short>>);
    ASSERT_TRUE(NullableValueLike<std::optional<int>>);
    ASSERT_TRUE(NullableValueLike<std::optional<unsigned int>>);
    ASSERT_TRUE(NullableValueLike<std::optional<long>>);
    ASSERT_TRUE(NullableValueLike<std::optional<unsigned long>>);
    ASSERT_TRUE(NullableValueLike<std::optional<long long>>);
    ASSERT_TRUE(NullableValueLike<std::optional<unsigned long long>>);

    ASSERT_TRUE(NullableValueLike<std::optional<float>>);
    ASSERT_TRUE(NullableValueLike<std::optional<double>>);
    ASSERT_TRUE(NullableValueLike<std::optional<long double>>);

    ASSERT_TRUE(NullableValueLike<std::optional<std::string>>);
}


TEST(ValueTypeTest, CompositeValueLike) {

    {
        using Type1 = std::tuple<int>;
        ASSERT_TRUE(CompositeValueLike<Type1>);
    }

    {
        using Type2 = std::tuple<int, std::string>;
        ASSERT_TRUE(CompositeValueLike<Type2>);
    }
}