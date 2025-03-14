#include <gtest/gtest.h>
#include <sqt/orm/value/trivial/basic/nullable_value_type.h>
#include <sqt/orm/value/trivial/basic/basic_value_traits_type.h>
#include <sqt/orm/value/trivial/basic/nullable_value_traits.h>

TEST(NullableValueTest, NullableValueType) {

    ASSERT_TRUE(sqt::NullableValueType<std::optional<bool>>);
    ASSERT_TRUE(sqt::NullableValueType<std::optional<char>>);
    ASSERT_TRUE(sqt::NullableValueType<std::optional<signed char>>);
    ASSERT_TRUE(sqt::NullableValueType<std::optional<unsigned char>>);
    ASSERT_TRUE(sqt::NullableValueType<std::optional<char8_t>>);
    ASSERT_TRUE(sqt::NullableValueType<std::optional<char16_t>>);
    ASSERT_TRUE(sqt::NullableValueType<std::optional<char32_t>>);
    ASSERT_TRUE(sqt::NullableValueType<std::optional<wchar_t>>);
    ASSERT_TRUE(sqt::NullableValueType<std::optional<short>>);
    ASSERT_TRUE(sqt::NullableValueType<std::optional<unsigned short>>);
    ASSERT_TRUE(sqt::NullableValueType<std::optional<int>>);
    ASSERT_TRUE(sqt::NullableValueType<std::optional<unsigned int>>);
    ASSERT_TRUE(sqt::NullableValueType<std::optional<long>>);
    ASSERT_TRUE(sqt::NullableValueType<std::optional<unsigned long>>);
    ASSERT_TRUE(sqt::NullableValueType<std::optional<long long>>);
    ASSERT_TRUE(sqt::NullableValueType<std::optional<unsigned long long>>);
    ASSERT_TRUE(sqt::NullableValueType<std::optional<float>>);
    ASSERT_TRUE(sqt::NullableValueType<std::optional<double>>);
    ASSERT_TRUE(sqt::NullableValueType<std::optional<long double>>);
    ASSERT_TRUE(sqt::NullableValueType<std::optional<std::string>>);

    ASSERT_FALSE(sqt::NullableValueType<bool>);
    ASSERT_FALSE(sqt::NullableValueType<char>);
    ASSERT_FALSE(sqt::NullableValueType<signed char>);
    ASSERT_FALSE(sqt::NullableValueType<unsigned char>);
    ASSERT_FALSE(sqt::NullableValueType<char8_t>);
    ASSERT_FALSE(sqt::NullableValueType<char16_t>);
    ASSERT_FALSE(sqt::NullableValueType<char32_t>);
    ASSERT_FALSE(sqt::NullableValueType<wchar_t>);
    ASSERT_FALSE(sqt::NullableValueType<short>);
    ASSERT_FALSE(sqt::NullableValueType<unsigned short>);
    ASSERT_FALSE(sqt::NullableValueType<int>);
    ASSERT_FALSE(sqt::NullableValueType<unsigned int>);
    ASSERT_FALSE(sqt::NullableValueType<long>);
    ASSERT_FALSE(sqt::NullableValueType<unsigned long>);
    ASSERT_FALSE(sqt::NullableValueType<long long>);
    ASSERT_FALSE(sqt::NullableValueType<unsigned long long>);
    ASSERT_FALSE(sqt::NullableValueType<float>);
    ASSERT_FALSE(sqt::NullableValueType<double>);
    ASSERT_FALSE(sqt::NullableValueType<long double>);
    ASSERT_FALSE(sqt::NullableValueType<std::string>);
}


TEST(NullableValueType, DataType) {

    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<bool>>::DataType, 
        sqt::DataType::Integer);
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<char>>::DataType, 
        sqt::DataType::Integer);
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<signed char>>::DataType,
        sqt::DataType::Integer);
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<unsigned char>>::DataType,
        sqt::DataType::Integer);
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<char8_t>>::DataType,
        sqt::DataType::Integer);
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<char16_t>>::DataType,
        sqt::DataType::Integer);
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<char32_t>>::DataType,
        sqt::DataType::Integer);
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<wchar_t>>::DataType,
        sqt::DataType::Integer);
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<short>>::DataType,
        sqt::DataType::Integer);
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<unsigned short>>::DataType,
        sqt::DataType::Integer);
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<int>>::DataType,
        sqt::DataType::Integer);
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<unsigned int>>::DataType,
        sqt::DataType::Integer);
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<long>>::DataType,
        sqt::DataType::Integer);
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<unsigned long>>::DataType,
        sqt::DataType::Integer);
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<long long>>::DataType,
        sqt::DataType::Integer);
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<unsigned long long>>::DataType,
        sqt::DataType::Integer);
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<float>>::DataType,
        sqt::DataType::Float);
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<double>>::DataType,
        sqt::DataType::Float);
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<long double>>::DataType,
        sqt::DataType::Float);
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<std::string>>::DataType,
        sqt::DataType::Text);
}


TEST(NullableValueType, IsNullable) {

    ASSERT_TRUE(sqt::NullableValueTraits<std::optional<bool>>::IsNullable);
    ASSERT_TRUE(sqt::NullableValueTraits<std::optional<char>>::IsNullable);
    ASSERT_TRUE(sqt::NullableValueTraits<std::optional<signed char>>::IsNullable);
    ASSERT_TRUE(sqt::NullableValueTraits<std::optional<unsigned char>>::IsNullable);
    ASSERT_TRUE(sqt::NullableValueTraits<std::optional<char8_t>>::IsNullable);
    ASSERT_TRUE(sqt::NullableValueTraits<std::optional<char16_t>>::IsNullable);
    ASSERT_TRUE(sqt::NullableValueTraits<std::optional<char32_t>>::IsNullable);
    ASSERT_TRUE(sqt::NullableValueTraits<std::optional<wchar_t>>::IsNullable);
    ASSERT_TRUE(sqt::NullableValueTraits<std::optional<short>>::IsNullable);
    ASSERT_TRUE(sqt::NullableValueTraits<std::optional<unsigned short>>::IsNullable);
    ASSERT_TRUE(sqt::NullableValueTraits<std::optional<int>>::IsNullable);
    ASSERT_TRUE(sqt::NullableValueTraits<std::optional<unsigned int>>::IsNullable);
    ASSERT_TRUE(sqt::NullableValueTraits<std::optional<long>>::IsNullable);
    ASSERT_TRUE(sqt::NullableValueTraits<std::optional<unsigned long>>::IsNullable);
    ASSERT_TRUE(sqt::NullableValueTraits<std::optional<long long>>::IsNullable);
    ASSERT_TRUE(sqt::NullableValueTraits<std::optional<unsigned long long>>::IsNullable);
    ASSERT_TRUE(sqt::NullableValueTraits<std::optional<float>>::IsNullable);
    ASSERT_TRUE(sqt::NullableValueTraits<std::optional<double>>::IsNullable);
    ASSERT_TRUE(sqt::NullableValueTraits<std::optional<long double>>::IsNullable);
    ASSERT_TRUE(sqt::NullableValueTraits<std::optional<std::string>>::IsNullable);
}


TEST(NullableValueType, BasicValueTriatsType) {

    ASSERT_TRUE(
        sqt::BasicValueTraitsType<sqt::NullableValueTraits<std::optional<bool>>>);
    ASSERT_TRUE(
        sqt::BasicValueTraitsType<sqt::NullableValueTraits<std::optional<char>>>);
    ASSERT_TRUE(
        sqt::BasicValueTraitsType<sqt::NullableValueTraits<std::optional<signed char>>>);
    ASSERT_TRUE(
        sqt::BasicValueTraitsType<sqt::NullableValueTraits<std::optional<unsigned char>>>);
    ASSERT_TRUE(
        sqt::BasicValueTraitsType<sqt::NullableValueTraits<std::optional<char8_t>>>);
    ASSERT_TRUE(
        sqt::BasicValueTraitsType<sqt::NullableValueTraits<std::optional<char16_t>>>);
    ASSERT_TRUE(
        sqt::BasicValueTraitsType<sqt::NullableValueTraits<std::optional<char32_t>>>);
    ASSERT_TRUE(
        sqt::BasicValueTraitsType<sqt::NullableValueTraits<std::optional<wchar_t>>>);
    ASSERT_TRUE(
        sqt::BasicValueTraitsType<sqt::NullableValueTraits<std::optional<short>>>);
    ASSERT_TRUE(
        sqt::BasicValueTraitsType<sqt::NullableValueTraits<std::optional<unsigned short>>>);
    ASSERT_TRUE(
        sqt::BasicValueTraitsType<sqt::NullableValueTraits<std::optional<int>>>);
    ASSERT_TRUE(
        sqt::BasicValueTraitsType<sqt::NullableValueTraits<std::optional<unsigned int>>>);
    ASSERT_TRUE(
        sqt::BasicValueTraitsType<sqt::NullableValueTraits<std::optional<long>>>);
    ASSERT_TRUE(
        sqt::BasicValueTraitsType<sqt::NullableValueTraits<std::optional<unsigned long>>>);
    ASSERT_TRUE(
        sqt::BasicValueTraitsType<sqt::NullableValueTraits<std::optional<long long>>>);
    ASSERT_TRUE(
        sqt::BasicValueTraitsType<sqt::NullableValueTraits<std::optional<unsigned long long>>>);
    ASSERT_TRUE(
        sqt::BasicValueTraitsType<sqt::NullableValueTraits<std::optional<float>>>);
    ASSERT_TRUE(
        sqt::BasicValueTraitsType<sqt::NullableValueTraits<std::optional<double>>>);
    ASSERT_TRUE(
        sqt::BasicValueTraitsType<sqt::NullableValueTraits<std::optional<long double>>>);
    ASSERT_TRUE(
        sqt::BasicValueTraitsType<sqt::NullableValueTraits<std::optional<std::string>>>);
}