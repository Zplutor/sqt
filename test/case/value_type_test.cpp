#include <gtest/gtest.h>
#include <sqt/orm/value/composite_value_type.h>
#include <sqt/orm/value/data_type_mapping.h>

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


TEST(ValueTypeTest, PrimitiveValueType) {

    ASSERT_TRUE(PrimitiveValueType<bool>);

    ASSERT_TRUE(PrimitiveValueType<char>);
    ASSERT_TRUE(PrimitiveValueType<signed char>);
    ASSERT_TRUE(PrimitiveValueType<unsigned char>);
    ASSERT_TRUE(PrimitiveValueType<char8_t>);
    ASSERT_TRUE(PrimitiveValueType<char16_t>);
    ASSERT_TRUE(PrimitiveValueType<char32_t>);
    ASSERT_TRUE(PrimitiveValueType<wchar_t>);

    ASSERT_TRUE(PrimitiveValueType<short>);
    ASSERT_TRUE(PrimitiveValueType<unsigned short>);
    ASSERT_TRUE(PrimitiveValueType<int>);
    ASSERT_TRUE(PrimitiveValueType<unsigned int>);
    ASSERT_TRUE(PrimitiveValueType<long>);
    ASSERT_TRUE(PrimitiveValueType<unsigned long>);
    ASSERT_TRUE(PrimitiveValueType<long long>);
    ASSERT_TRUE(PrimitiveValueType<unsigned long long>);

    ASSERT_TRUE(PrimitiveValueType<float>);
    ASSERT_TRUE(PrimitiveValueType<double>);
    ASSERT_TRUE(PrimitiveValueType<long double>);

    ASSERT_TRUE(PrimitiveValueType<std::string>);
}


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