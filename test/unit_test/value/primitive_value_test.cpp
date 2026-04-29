#include <gtest/gtest.h>
#include <sqt/orm/value/trivial/basic/basic_value_traits_mapping.h>
#include <sqt/orm/value/trivial/basic/basic_value_traits_type.h>
#include <sqt/orm/value/trivial/basic/primitive_value_type.h>

// Test enums
enum class SmallEnum : unsigned char {
    Value1 = 0,
    Value2 = 1
};

enum class LargeEnum : std::int64_t {
    Value1 = 0,
    Value2 = 1
};

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

    static_assert(sqt::PrimitiveValueType<SmallEnum>);
    static_assert(sqt::PrimitiveValueType<LargeEnum>);

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

    ASSERT_EQ(sqt::PrimitiveValueTraits<SmallEnum>::DataType, sqt::DataType::Integer);
    ASSERT_EQ(sqt::PrimitiveValueTraits<LargeEnum>::DataType, sqt::DataType::Integer);
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

    static_assert(!sqt::PrimitiveValueTraits<SmallEnum>::IsNullable);
    static_assert(!sqt::PrimitiveValueTraits<LargeEnum>::IsNullable);
}


TEST(PrimitiveValueTest, ToSQLLiteral) {

    // bool
    ASSERT_EQ(sqt::PrimitiveValueTraits<bool>::ToSQLLiteral(true), "1");
    ASSERT_EQ(sqt::PrimitiveValueTraits<bool>::ToSQLLiteral(false), "0");

    // integral types
    ASSERT_EQ(sqt::PrimitiveValueTraits<char>::ToSQLLiteral('A'), "65");
    ASSERT_EQ(sqt::PrimitiveValueTraits<signed char>::ToSQLLiteral(-12), "-12");
    ASSERT_EQ(sqt::PrimitiveValueTraits<unsigned char>::ToSQLLiteral(250), "250");
    ASSERT_EQ(sqt::PrimitiveValueTraits<char8_t>::ToSQLLiteral(u8'Z'), "90");
    ASSERT_EQ(sqt::PrimitiveValueTraits<char16_t>::ToSQLLiteral(u'\u4E2D'), "20013");
    ASSERT_EQ(sqt::PrimitiveValueTraits<char32_t>::ToSQLLiteral(U'\U0001F600'), "128512");
    ASSERT_EQ(sqt::PrimitiveValueTraits<wchar_t>::ToSQLLiteral(L'X'), "88");
    ASSERT_EQ(sqt::PrimitiveValueTraits<short>::ToSQLLiteral(-32123), "-32123");
    ASSERT_EQ(sqt::PrimitiveValueTraits<unsigned short>::ToSQLLiteral(54321), "54321");
    ASSERT_EQ(sqt::PrimitiveValueTraits<int>::ToSQLLiteral(42), "42");
    ASSERT_EQ(sqt::PrimitiveValueTraits<unsigned int>::ToSQLLiteral(4000000000u), "4000000000");
    ASSERT_EQ(sqt::PrimitiveValueTraits<long>::ToSQLLiteral(-123456789l), "-123456789");
    ASSERT_EQ(sqt::PrimitiveValueTraits<unsigned long>::ToSQLLiteral(123456789ul), "123456789");
    ASSERT_EQ(
        sqt::PrimitiveValueTraits<long long>::ToSQLLiteral(-1234567890123ll), 
        "-1234567890123");
    ASSERT_EQ(
        sqt::PrimitiveValueTraits<unsigned long long>::ToSQLLiteral(1234567890123ull),
        "1234567890123");

    // floating-point types
    ASSERT_EQ(sqt::PrimitiveValueTraits<float>::ToSQLLiteral(3.14f), "3.140000");
    ASSERT_EQ(sqt::PrimitiveValueTraits<float>::ToSQLLiteral(-2.5f), "-2.500000");
    ASSERT_EQ(sqt::PrimitiveValueTraits<double>::ToSQLLiteral(3.1415926), "3.141593");
    ASSERT_EQ(sqt::PrimitiveValueTraits<double>::ToSQLLiteral(-2.5), "-2.500000");

    // string type
    ASSERT_EQ(sqt::PrimitiveValueTraits<std::string>::ToSQLLiteral("Hello"), "'Hello'");
    ASSERT_EQ(sqt::PrimitiveValueTraits<std::string>::ToSQLLiteral("He'llo"), "'He''llo'");
    ASSERT_EQ(
        sqt::PrimitiveValueTraits<std::string>::ToSQLLiteral("Hello World 123"),
        "'Hello World 123'");

    // enum types
    ASSERT_EQ(sqt::PrimitiveValueTraits<SmallEnum>::ToSQLLiteral(SmallEnum::Value1), "0");
    ASSERT_EQ(sqt::PrimitiveValueTraits<SmallEnum>::ToSQLLiteral(SmallEnum::Value2), "1");
    ASSERT_EQ(sqt::PrimitiveValueTraits<LargeEnum>::ToSQLLiteral(LargeEnum::Value1), "0");
    ASSERT_EQ(sqt::PrimitiveValueTraits<LargeEnum>::ToSQLLiteral(LargeEnum::Value2), "1");
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

    static_assert(sqt::BasicValueTraitsType<sqt::PrimitiveValueTraits<SmallEnum>>);
    static_assert(sqt::BasicValueTraitsType<sqt::PrimitiveValueTraits<LargeEnum>>);
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

    static_assert((std::is_same_v<
        sqt::BasicValueTraitsMappingT<SmallEnum>,
        sqt::PrimitiveValueTraits<SmallEnum>>));
    static_assert((std::is_same_v<
        sqt::BasicValueTraitsMappingT<LargeEnum>,
        sqt::PrimitiveValueTraits<LargeEnum>>));
}