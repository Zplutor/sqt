#include <gtest/gtest.h>
#include <sqt/orm/value/trivial/basic/basic_value_traits_mapping.h>
#include <sqt/orm/value/trivial/basic/nullable_value_type.h>
#include <sqt/orm/value/trivial/basic/basic_value_traits_type.h>
#include <sqt/orm/value/trivial/basic/nullable_value_traits.h>

TEST(NullableValueTest, NullableValueType) {

    static_assert(sqt::NullableValueType<std::optional<bool>>);
    static_assert(sqt::NullableValueType<std::optional<char>>);
    static_assert(sqt::NullableValueType<std::optional<signed char>>);
    static_assert(sqt::NullableValueType<std::optional<unsigned char>>);
    static_assert(sqt::NullableValueType<std::optional<char8_t>>);
    static_assert(sqt::NullableValueType<std::optional<char16_t>>);
    static_assert(sqt::NullableValueType<std::optional<char32_t>>);
    static_assert(sqt::NullableValueType<std::optional<wchar_t>>);
    static_assert(sqt::NullableValueType<std::optional<short>>);
    static_assert(sqt::NullableValueType<std::optional<unsigned short>>);
    static_assert(sqt::NullableValueType<std::optional<int>>);
    static_assert(sqt::NullableValueType<std::optional<unsigned int>>);
    static_assert(sqt::NullableValueType<std::optional<long>>);
    static_assert(sqt::NullableValueType<std::optional<unsigned long>>);
    static_assert(sqt::NullableValueType<std::optional<long long>>);
    static_assert(sqt::NullableValueType<std::optional<unsigned long long>>);
    static_assert(sqt::NullableValueType<std::optional<float>>);
    static_assert(sqt::NullableValueType<std::optional<double>>);
    static_assert(sqt::NullableValueType<std::optional<std::string>>);

    static_assert(!sqt::NullableValueType<std::optional<long double>>);
    static_assert(!sqt::NullableValueType<bool>);
    static_assert(!sqt::NullableValueType<char>);
    static_assert(!sqt::NullableValueType<signed char>);
    static_assert(!sqt::NullableValueType<unsigned char>);
    static_assert(!sqt::NullableValueType<char8_t>);
    static_assert(!sqt::NullableValueType<char16_t>);
    static_assert(!sqt::NullableValueType<char32_t>);
    static_assert(!sqt::NullableValueType<wchar_t>);
    static_assert(!sqt::NullableValueType<short>);
    static_assert(!sqt::NullableValueType<unsigned short>);
    static_assert(!sqt::NullableValueType<int>);
    static_assert(!sqt::NullableValueType<unsigned int>);
    static_assert(!sqt::NullableValueType<long>);
    static_assert(!sqt::NullableValueType<unsigned long>);
    static_assert(!sqt::NullableValueType<long long>);
    static_assert(!sqt::NullableValueType<unsigned long long>);
    static_assert(!sqt::NullableValueType<float>);
    static_assert(!sqt::NullableValueType<double>);
    static_assert(!sqt::NullableValueType<long double>);
    static_assert(!sqt::NullableValueType<std::string>);
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
        sqt::NullableValueTraits<std::optional<std::string>>::DataType,
        sqt::DataType::Text);
}


TEST(NullableValueType, IsNullable) {

    static_assert(sqt::NullableValueTraits<std::optional<bool>>::IsNullable);
    static_assert(sqt::NullableValueTraits<std::optional<char>>::IsNullable);
    static_assert(sqt::NullableValueTraits<std::optional<signed char>>::IsNullable);
    static_assert(sqt::NullableValueTraits<std::optional<unsigned char>>::IsNullable);
    static_assert(sqt::NullableValueTraits<std::optional<char8_t>>::IsNullable);
    static_assert(sqt::NullableValueTraits<std::optional<char16_t>>::IsNullable);
    static_assert(sqt::NullableValueTraits<std::optional<char32_t>>::IsNullable);
    static_assert(sqt::NullableValueTraits<std::optional<wchar_t>>::IsNullable);
    static_assert(sqt::NullableValueTraits<std::optional<short>>::IsNullable);
    static_assert(sqt::NullableValueTraits<std::optional<unsigned short>>::IsNullable);
    static_assert(sqt::NullableValueTraits<std::optional<int>>::IsNullable);
    static_assert(sqt::NullableValueTraits<std::optional<unsigned int>>::IsNullable);
    static_assert(sqt::NullableValueTraits<std::optional<long>>::IsNullable);
    static_assert(sqt::NullableValueTraits<std::optional<unsigned long>>::IsNullable);
    static_assert(sqt::NullableValueTraits<std::optional<long long>>::IsNullable);
    static_assert(sqt::NullableValueTraits<std::optional<unsigned long long>>::IsNullable);
    static_assert(sqt::NullableValueTraits<std::optional<float>>::IsNullable);
    static_assert(sqt::NullableValueTraits<std::optional<double>>::IsNullable);
    static_assert(sqt::NullableValueTraits<std::optional<std::string>>::IsNullable);
}


TEST(NullableValueType, ToSQLLiteral) {

    // bool
    ASSERT_EQ(sqt::NullableValueTraits<std::optional<bool>>::ToSQLLiteral(std::nullopt), "null");
    ASSERT_EQ(sqt::NullableValueTraits<std::optional<bool>>::ToSQLLiteral(true), "1");
    ASSERT_EQ(sqt::NullableValueTraits<std::optional<bool>>::ToSQLLiteral(false), "0");

    // integral types
    ASSERT_EQ(sqt::NullableValueTraits<std::optional<char>>::ToSQLLiteral(std::nullopt), "null");
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<char>>::ToSQLLiteral('A'),
        "65");
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<signed char>>::ToSQLLiteral(std::nullopt),
        "null");
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<signed char>>::ToSQLLiteral(
            static_cast<signed char>(-12)),
        "-12");
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<unsigned char>>::ToSQLLiteral(std::nullopt),
        "null");
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<unsigned char>>::ToSQLLiteral(
            static_cast<unsigned char>(250)),
        "250");
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<char8_t>>::ToSQLLiteral(std::nullopt),
        "null");
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<char8_t>>::ToSQLLiteral(u8'Z'),
        "90");
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<char16_t>>::ToSQLLiteral(std::nullopt),
        "null");
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<char16_t>>::ToSQLLiteral(u'\u4E2D'),
        "20013");
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<char32_t>>::ToSQLLiteral(std::nullopt),
        "null");
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<char32_t>>::ToSQLLiteral(U'\U0001F600'),
        "128512");
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<wchar_t>>::ToSQLLiteral(std::nullopt),
        "null");
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<wchar_t>>::ToSQLLiteral(L'X'),
        "88");
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<short>>::ToSQLLiteral(std::nullopt),
        "null");
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<short>>::ToSQLLiteral(static_cast<short>(-32123)),
        "-32123");
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<unsigned short>>::ToSQLLiteral(std::nullopt),
        "null");
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<unsigned short>>::ToSQLLiteral(
            static_cast<unsigned short>(54321)),
        "54321");
    ASSERT_EQ(sqt::NullableValueTraits<std::optional<int>>::ToSQLLiteral(std::nullopt), "null");
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<int>>::ToSQLLiteral(42),
        "42");
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<unsigned int>>::ToSQLLiteral(std::nullopt),
        "null");
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<unsigned int>>::ToSQLLiteral(
            4000000000u),
        "4000000000");
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<long>>::ToSQLLiteral(std::nullopt),
        "null");
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<long>>::ToSQLLiteral(-123456789l),
        "-123456789");
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<unsigned long>>::ToSQLLiteral(std::nullopt),
        "null");
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<unsigned long>>::ToSQLLiteral(123456789ul),
        "123456789");
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<long long>>::ToSQLLiteral(std::nullopt),
        "null");
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<long long>>::ToSQLLiteral(-1234567890123ll),
        "-1234567890123");
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<unsigned long long>>::ToSQLLiteral(std::nullopt),
        "null");
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<unsigned long long>>::ToSQLLiteral(1234567890ull),
        "1234567890");

    // floating-point types
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<float>>::ToSQLLiteral(std::nullopt),
        "null");
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<float>>::ToSQLLiteral(3.14f),
        "3.140000");
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<float>>::ToSQLLiteral(-2.5f),
        "-2.500000");
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<double>>::ToSQLLiteral(std::nullopt),
        "null");
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<double>>::ToSQLLiteral(3.1415926),
        "3.141593");
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<double>>::ToSQLLiteral(-2.5),
        "-2.500000");

    // string type
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<std::string>>::ToSQLLiteral(std::nullopt),
        "null");
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<std::string>>::ToSQLLiteral("Hello"),
        "'Hello'");
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<std::string>>::ToSQLLiteral("He'llo"),
        "'He''llo'");
    ASSERT_EQ(
        sqt::NullableValueTraits<std::optional<std::string>>::ToSQLLiteral("Hello World 123"),
        "'Hello World 123'");
}


TEST(NullableValueType, BasicValueTriatsType) {

    static_assert(
        sqt::BasicValueTraitsType<sqt::NullableValueTraits<std::optional<bool>>>);
    static_assert(
        sqt::BasicValueTraitsType<sqt::NullableValueTraits<std::optional<char>>>);
    static_assert(
        sqt::BasicValueTraitsType<sqt::NullableValueTraits<std::optional<signed char>>>);
    static_assert(
        sqt::BasicValueTraitsType<sqt::NullableValueTraits<std::optional<unsigned char>>>);
    static_assert(
        sqt::BasicValueTraitsType<sqt::NullableValueTraits<std::optional<char8_t>>>);
    static_assert(
        sqt::BasicValueTraitsType<sqt::NullableValueTraits<std::optional<char16_t>>>);
    static_assert(
        sqt::BasicValueTraitsType<sqt::NullableValueTraits<std::optional<char32_t>>>);
    static_assert(
        sqt::BasicValueTraitsType<sqt::NullableValueTraits<std::optional<wchar_t>>>);
    static_assert(
        sqt::BasicValueTraitsType<sqt::NullableValueTraits<std::optional<short>>>);
    static_assert(
        sqt::BasicValueTraitsType<sqt::NullableValueTraits<std::optional<unsigned short>>>);
    static_assert(
        sqt::BasicValueTraitsType<sqt::NullableValueTraits<std::optional<int>>>);
    static_assert(
        sqt::BasicValueTraitsType<sqt::NullableValueTraits<std::optional<unsigned int>>>);
    static_assert(
        sqt::BasicValueTraitsType<sqt::NullableValueTraits<std::optional<long>>>);
    static_assert(
        sqt::BasicValueTraitsType<sqt::NullableValueTraits<std::optional<unsigned long>>>);
    static_assert(
        sqt::BasicValueTraitsType<sqt::NullableValueTraits<std::optional<long long>>>);
    static_assert(
        sqt::BasicValueTraitsType<sqt::NullableValueTraits<std::optional<unsigned long long>>>);
    static_assert(
        sqt::BasicValueTraitsType<sqt::NullableValueTraits<std::optional<float>>>);
    static_assert(
        sqt::BasicValueTraitsType<sqt::NullableValueTraits<std::optional<double>>>);
    static_assert(
        sqt::BasicValueTraitsType<sqt::NullableValueTraits<std::optional<std::string>>>);
}


TEST(NullableValueType, BasicValueTraitsMapping) {

    static_assert((std::is_same_v<
        sqt::BasicValueTraitsMappingT<std::optional<bool>>,
        sqt::NullableValueTraits<std::optional<bool>>>));
    static_assert((std::is_same_v<
        sqt::BasicValueTraitsMappingT<std::optional<int>>,
        sqt::NullableValueTraits<std::optional<int>>>));
    static_assert((std::is_same_v<
        sqt::BasicValueTraitsMappingT<std::optional<float>>,
        sqt::NullableValueTraits<std::optional<float>>>));
    static_assert((std::is_same_v<
        sqt::BasicValueTraitsMappingT<std::optional<std::string>>,
        sqt::NullableValueTraits<std::optional<std::string>>>));
}