#include <gtest/gtest.h>
#include <sqt/orm/value/trivial/basic/basic_value_traits_mapping.h>
#include <sqt/orm/value/trivial/basic/basic_value_traits_type.h>
#include <sqt/orm/value/trivial/basic/primitive_value_type.h>

TEST(PrimitiveValueTest, PrimitiveValueType) {

    ASSERT_TRUE(sqt::PrimitiveValueType<bool>);
    ASSERT_TRUE(sqt::PrimitiveValueType<char>);
    ASSERT_TRUE(sqt::PrimitiveValueType<signed char>);
    ASSERT_TRUE(sqt::PrimitiveValueType<unsigned char>);
    ASSERT_TRUE(sqt::PrimitiveValueType<char8_t>);
    ASSERT_TRUE(sqt::PrimitiveValueType<char16_t>);
    ASSERT_TRUE(sqt::PrimitiveValueType<char32_t>);
    ASSERT_TRUE(sqt::PrimitiveValueType<wchar_t>);
    ASSERT_TRUE(sqt::PrimitiveValueType<short>);
    ASSERT_TRUE(sqt::PrimitiveValueType<unsigned short>);
    ASSERT_TRUE(sqt::PrimitiveValueType<int>);
    ASSERT_TRUE(sqt::PrimitiveValueType<unsigned int>);
    ASSERT_TRUE(sqt::PrimitiveValueType<long>);
    ASSERT_TRUE(sqt::PrimitiveValueType<unsigned long>);
    ASSERT_TRUE(sqt::PrimitiveValueType<long long>);
    ASSERT_TRUE(sqt::PrimitiveValueType<unsigned long long>);
    ASSERT_TRUE(sqt::PrimitiveValueType<float>);
    ASSERT_TRUE(sqt::PrimitiveValueType<double>);
    ASSERT_TRUE(sqt::PrimitiveValueType<long double>);
    ASSERT_TRUE(sqt::PrimitiveValueType<std::string>);

    ASSERT_FALSE(sqt::PrimitiveValueType<std::optional<int>>);
    ASSERT_FALSE(sqt::PrimitiveValueType<std::vector<int>>);
}


TEST(PrimitiveValueTest, DataType) {

    ASSERT_EQ(sqt::PrimitiveValueTraits<bool>::DataType, sqt::DataType::Integer);
    ASSERT_EQ(sqt::PrimitiveValueTraits<char>::DataType, sqt::DataType::Integer);
    ASSERT_EQ(sqt::PrimitiveValueTraits<signed char>::DataType, sqt::DataType::Integer);
    ASSERT_EQ(sqt::PrimitiveValueTraits<unsigned char>::DataType, sqt::DataType::Integer);
    ASSERT_EQ(sqt::PrimitiveValueTraits<char8_t>::DataType, sqt::DataType::Integer);
    ASSERT_EQ(sqt::PrimitiveValueTraits<char16_t>::DataType, sqt::DataType::Integer);
    ASSERT_EQ(sqt::PrimitiveValueTraits<char32_t>::DataType, sqt::DataType::Integer);
    ASSERT_EQ(sqt::PrimitiveValueTraits<wchar_t>::DataType, sqt::DataType::Integer);
    ASSERT_EQ(sqt::PrimitiveValueTraits<short>::DataType, sqt::DataType::Integer);
    ASSERT_EQ(sqt::PrimitiveValueTraits<unsigned short>::DataType, sqt::DataType::Integer);
    ASSERT_EQ(sqt::PrimitiveValueTraits<int>::DataType, sqt::DataType::Integer);
    ASSERT_EQ(sqt::PrimitiveValueTraits<unsigned int>::DataType, sqt::DataType::Integer);
    ASSERT_EQ(sqt::PrimitiveValueTraits<long>::DataType, sqt::DataType::Integer);
    ASSERT_EQ(sqt::PrimitiveValueTraits<unsigned long>::DataType, sqt::DataType::Integer);
    ASSERT_EQ(sqt::PrimitiveValueTraits<long long>::DataType, sqt::DataType::Integer);
    ASSERT_EQ(sqt::PrimitiveValueTraits<unsigned long long>::DataType, sqt::DataType::Integer);
    ASSERT_EQ(sqt::PrimitiveValueTraits<float>::DataType, sqt::DataType::Float);
    ASSERT_EQ(sqt::PrimitiveValueTraits<double>::DataType, sqt::DataType::Float);
    ASSERT_EQ(sqt::PrimitiveValueTraits<long double>::DataType, sqt::DataType::Float);
    ASSERT_EQ(sqt::PrimitiveValueTraits<std::string>::DataType, sqt::DataType::Text);
}


TEST(PrimitiveValueTest, IsNullable) {

    ASSERT_FALSE(sqt::PrimitiveValueTraits<bool>::IsNullable);
    ASSERT_FALSE(sqt::PrimitiveValueTraits<char>::IsNullable);
    ASSERT_FALSE(sqt::PrimitiveValueTraits<signed char>::IsNullable);
    ASSERT_FALSE(sqt::PrimitiveValueTraits<unsigned char>::IsNullable);
    ASSERT_FALSE(sqt::PrimitiveValueTraits<char8_t>::IsNullable);
    ASSERT_FALSE(sqt::PrimitiveValueTraits<char16_t>::IsNullable);
    ASSERT_FALSE(sqt::PrimitiveValueTraits<char32_t>::IsNullable);
    ASSERT_FALSE(sqt::PrimitiveValueTraits<wchar_t>::IsNullable);
    ASSERT_FALSE(sqt::PrimitiveValueTraits<short>::IsNullable);
    ASSERT_FALSE(sqt::PrimitiveValueTraits<unsigned short>::IsNullable);
    ASSERT_FALSE(sqt::PrimitiveValueTraits<int>::IsNullable);
    ASSERT_FALSE(sqt::PrimitiveValueTraits<unsigned int>::IsNullable);
    ASSERT_FALSE(sqt::PrimitiveValueTraits<long>::IsNullable);
    ASSERT_FALSE(sqt::PrimitiveValueTraits<unsigned long>::IsNullable);
    ASSERT_FALSE(sqt::PrimitiveValueTraits<long long>::IsNullable);
    ASSERT_FALSE(sqt::PrimitiveValueTraits<unsigned long long>::IsNullable);
    ASSERT_FALSE(sqt::PrimitiveValueTraits<float>::IsNullable);
    ASSERT_FALSE(sqt::PrimitiveValueTraits<double>::IsNullable);
    ASSERT_FALSE(sqt::PrimitiveValueTraits<long double>::IsNullable);
    ASSERT_FALSE(sqt::PrimitiveValueTraits<std::string>::IsNullable);
}


TEST(PrimitiveValueTest, BasicValueTraitsType) {

    ASSERT_TRUE(sqt::BasicValueTraitsType<sqt::PrimitiveValueTraits<bool>>);
    ASSERT_TRUE(sqt::BasicValueTraitsType<sqt::PrimitiveValueTraits<char>>);
    ASSERT_TRUE(sqt::BasicValueTraitsType<sqt::PrimitiveValueTraits<signed char>>);
    ASSERT_TRUE(sqt::BasicValueTraitsType<sqt::PrimitiveValueTraits<unsigned char>>);
    ASSERT_TRUE(sqt::BasicValueTraitsType<sqt::PrimitiveValueTraits<char8_t>>);
    ASSERT_TRUE(sqt::BasicValueTraitsType<sqt::PrimitiveValueTraits<char16_t>>);
    ASSERT_TRUE(sqt::BasicValueTraitsType<sqt::PrimitiveValueTraits<char32_t>>);
    ASSERT_TRUE(sqt::BasicValueTraitsType<sqt::PrimitiveValueTraits<wchar_t>>);
    ASSERT_TRUE(sqt::BasicValueTraitsType<sqt::PrimitiveValueTraits<short>>);
    ASSERT_TRUE(sqt::BasicValueTraitsType<sqt::PrimitiveValueTraits<unsigned short>>);
    ASSERT_TRUE(sqt::BasicValueTraitsType<sqt::PrimitiveValueTraits<int>>);
    ASSERT_TRUE(sqt::BasicValueTraitsType<sqt::PrimitiveValueTraits<unsigned int>>);
    ASSERT_TRUE(sqt::BasicValueTraitsType<sqt::PrimitiveValueTraits<long>>);
    ASSERT_TRUE(sqt::BasicValueTraitsType<sqt::PrimitiveValueTraits<unsigned long>>);
    ASSERT_TRUE(sqt::BasicValueTraitsType<sqt::PrimitiveValueTraits<long long>>);
    ASSERT_TRUE(sqt::BasicValueTraitsType<sqt::PrimitiveValueTraits<unsigned long long>>);
    ASSERT_TRUE(sqt::BasicValueTraitsType<sqt::PrimitiveValueTraits<float>>);
    ASSERT_TRUE(sqt::BasicValueTraitsType<sqt::PrimitiveValueTraits<double>>);
    ASSERT_TRUE(sqt::BasicValueTraitsType<sqt::PrimitiveValueTraits<long double>>);
    ASSERT_TRUE(sqt::BasicValueTraitsType<sqt::PrimitiveValueTraits<std::string>>);
}


TEST(PrimitiveValueTest, BasicValueTraitsMapping) {

    ASSERT_TRUE((std::is_same_v<
        sqt::BasicValueTraitsForT<bool>,
        sqt::PrimitiveValueTraits<bool>>));
    ASSERT_TRUE((std::is_same_v<
        sqt::BasicValueTraitsForT<int>,
        sqt::PrimitiveValueTraits<int>>));
    ASSERT_TRUE((
        std::is_same_v<sqt::BasicValueTraitsForT<float>,
        sqt::PrimitiveValueTraits<float>>));
    ASSERT_TRUE((std::is_same_v<
        sqt::BasicValueTraitsForT<std::string>,
        sqt::PrimitiveValueTraits<std::string>>));
}