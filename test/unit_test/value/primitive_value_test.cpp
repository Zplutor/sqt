#include <gtest/gtest.h>
#include <sqt/orm/value/trivial/basic/basic_value_traits_mapping.h>
#include <sqt/orm/value/trivial/basic/basic_value_traits_type.h>
#include <sqt/orm/value/trivial/basic/primitive_value_type.h>

TEST(PrimitiveValueTest, PrimitiveValueType) {

    static_assert(sqt::PrimitiveValueType<bool>);
    static_assert(sqt::PrimitiveValueType<char>);
    static_assert(sqt::PrimitiveValueType<signed char>);
    static_assert(sqt::PrimitiveValueType<unsigned char>);
    static_assert(sqt::PrimitiveValueType<char8_t>);
    static_assert(sqt::PrimitiveValueType<char16_t>);
    static_assert(sqt::PrimitiveValueType<char32_t>);
    static_assert(sqt::PrimitiveValueType<wchar_t>);
    static_assert(sqt::PrimitiveValueType<short>);
    static_assert(sqt::PrimitiveValueType<unsigned short>);
    static_assert(sqt::PrimitiveValueType<int>);
    static_assert(sqt::PrimitiveValueType<unsigned int>);
    static_assert(sqt::PrimitiveValueType<long>);
    static_assert(sqt::PrimitiveValueType<unsigned long>);
    static_assert(sqt::PrimitiveValueType<long long>);
    static_assert(sqt::PrimitiveValueType<unsigned long long>);
    static_assert(sqt::PrimitiveValueType<float>);
    static_assert(sqt::PrimitiveValueType<double>);
    static_assert(sqt::PrimitiveValueType<std::string>);

    static_assert(!sqt::PrimitiveValueType<long double>);
    static_assert(!sqt::PrimitiveValueType<std::optional<int>>);
    static_assert(!sqt::PrimitiveValueType<std::vector<int>>);
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
    ASSERT_EQ(sqt::PrimitiveValueTraits<std::string>::DataType, sqt::DataType::Text);
}


TEST(PrimitiveValueTest, IsNullable) {

    static_assert(!sqt::PrimitiveValueTraits<bool>::IsNullable);
    static_assert(!sqt::PrimitiveValueTraits<char>::IsNullable);
    static_assert(!sqt::PrimitiveValueTraits<signed char>::IsNullable);
    static_assert(!sqt::PrimitiveValueTraits<unsigned char>::IsNullable);
    static_assert(!sqt::PrimitiveValueTraits<char8_t>::IsNullable);
    static_assert(!sqt::PrimitiveValueTraits<char16_t>::IsNullable);
    static_assert(!sqt::PrimitiveValueTraits<char32_t>::IsNullable);
    static_assert(!sqt::PrimitiveValueTraits<wchar_t>::IsNullable);
    static_assert(!sqt::PrimitiveValueTraits<short>::IsNullable);
    static_assert(!sqt::PrimitiveValueTraits<unsigned short>::IsNullable);
    static_assert(!sqt::PrimitiveValueTraits<int>::IsNullable);
    static_assert(!sqt::PrimitiveValueTraits<unsigned int>::IsNullable);
    static_assert(!sqt::PrimitiveValueTraits<long>::IsNullable);
    static_assert(!sqt::PrimitiveValueTraits<unsigned long>::IsNullable);
    static_assert(!sqt::PrimitiveValueTraits<long long>::IsNullable);
    static_assert(!sqt::PrimitiveValueTraits<unsigned long long>::IsNullable);
    static_assert(!sqt::PrimitiveValueTraits<float>::IsNullable);
    static_assert(!sqt::PrimitiveValueTraits<double>::IsNullable);
    static_assert(!sqt::PrimitiveValueTraits<std::string>::IsNullable);
}


TEST(PrimitiveValueTest, BasicValueTraitsType) {

    static_assert(sqt::BasicValueTraitsType<sqt::PrimitiveValueTraits<bool>>);
    static_assert(sqt::BasicValueTraitsType<sqt::PrimitiveValueTraits<char>>);
    static_assert(sqt::BasicValueTraitsType<sqt::PrimitiveValueTraits<signed char>>);
    static_assert(sqt::BasicValueTraitsType<sqt::PrimitiveValueTraits<unsigned char>>);
    static_assert(sqt::BasicValueTraitsType<sqt::PrimitiveValueTraits<char8_t>>);
    static_assert(sqt::BasicValueTraitsType<sqt::PrimitiveValueTraits<char16_t>>);
    static_assert(sqt::BasicValueTraitsType<sqt::PrimitiveValueTraits<char32_t>>);
    static_assert(sqt::BasicValueTraitsType<sqt::PrimitiveValueTraits<wchar_t>>);
    static_assert(sqt::BasicValueTraitsType<sqt::PrimitiveValueTraits<short>>);
    static_assert(sqt::BasicValueTraitsType<sqt::PrimitiveValueTraits<unsigned short>>);
    static_assert(sqt::BasicValueTraitsType<sqt::PrimitiveValueTraits<int>>);
    static_assert(sqt::BasicValueTraitsType<sqt::PrimitiveValueTraits<unsigned int>>);
    static_assert(sqt::BasicValueTraitsType<sqt::PrimitiveValueTraits<long>>);
    static_assert(sqt::BasicValueTraitsType<sqt::PrimitiveValueTraits<unsigned long>>);
    static_assert(sqt::BasicValueTraitsType<sqt::PrimitiveValueTraits<long long>>);
    static_assert(sqt::BasicValueTraitsType<sqt::PrimitiveValueTraits<unsigned long long>>);
    static_assert(sqt::BasicValueTraitsType<sqt::PrimitiveValueTraits<float>>);
    static_assert(sqt::BasicValueTraitsType<sqt::PrimitiveValueTraits<double>>);
    static_assert(sqt::BasicValueTraitsType<sqt::PrimitiveValueTraits<std::string>>);
}


TEST(PrimitiveValueTest, BasicValueTraitsMapping) {

    static_assert((std::is_same_v<
        sqt::BasicValueTraitsMappingT<bool>,
        sqt::PrimitiveValueTraits<bool>>));
    static_assert((std::is_same_v<
        sqt::BasicValueTraitsMappingT<int>,
        sqt::PrimitiveValueTraits<int>>));
    static_assert((
        std::is_same_v<sqt::BasicValueTraitsMappingT<float>,
        sqt::PrimitiveValueTraits<float>>));
    static_assert((std::is_same_v<
        sqt::BasicValueTraitsMappingT<std::string>,
        sqt::PrimitiveValueTraits<std::string>>));
}