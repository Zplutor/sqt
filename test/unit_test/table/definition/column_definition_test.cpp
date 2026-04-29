#include <concepts>
#include <gtest/gtest.h>
#include <sqt/orm/table_definition.h>
#include <sqt/orm/table_mapping.h>
#include <sqt/orm/table/column/value_source_type.h>
#include <sqt/orm/value/trivial/basic/basic_value_traits_type.h>

namespace column_def_test {
struct BasicEntity {
    int id{};
};
SQT_TABLE_BEGIN(BasicEntity, BasicEntity)
SQT_COLUMN_FIELD(ID, id)
SQT_TABLE_END
}

SQT_REGISTER(column_def_test::BasicEntity)

TEST(ColumnDefinitionTest, ColumnBasicInterface) {

    using ColumnType = sqt::TableType<column_def_test::BasicEntity>::ColumnType_ID;
    static_assert(!std::copyable<ColumnType>);
    static_assert(!std::movable<ColumnType>);

    ASSERT_EQ(ColumnType::Name, "ID");

    constexpr const auto& column = sqt::Table<column_def_test::BasicEntity>.ID;
    constexpr std::string_view name = column.GetName();
    ASSERT_EQ(name, "ID");

    std::optional<std::string> default_value = column.GetDefaultValueSQLLiteral();
    ASSERT_EQ(default_value, std::nullopt);
}


namespace column_def_test {
struct VariousValueEntity {
    bool bool_value{};
    char char_value{};
    signed char signed_char_value{};
    unsigned char unsigned_char_value{};
    char8_t char8_t_value{};
    char16_t char16_t_value{};
    char32_t char32_t_value{};
    wchar_t wchar_t_value{};
    short short_value{};
    unsigned short unsigned_short_value{};
    int int_value{};
    unsigned int unsigned_int_value{};
    long long_value{};
    unsigned long unsigned_long_value{};
    long long long_long_value{};
    unsigned long long unsigned_long_long_value{};
    float float_value{};
    double double_value{};
    std::string string_value;
};
SQT_TABLE_BEGIN(VariousValueEntity, VariousValueEntity)
SQT_COLUMN_FIELD(BoolValue, bool_value)
SQT_COLUMN_FIELD(CharValue, char_value)
SQT_COLUMN_FIELD(SignedCharValue, signed_char_value)
SQT_COLUMN_FIELD(UnsignedCharValue, unsigned_char_value)
SQT_COLUMN_FIELD(Char8TValue, char8_t_value)
SQT_COLUMN_FIELD(Char16TValue, char16_t_value)
SQT_COLUMN_FIELD(Char32TValue, char32_t_value)
SQT_COLUMN_FIELD(WCharTValue, wchar_t_value)
SQT_COLUMN_FIELD(ShortValue, short_value)
SQT_COLUMN_FIELD(UnsignedShortValue, unsigned_short_value)
SQT_COLUMN_FIELD(IntValue, int_value)
SQT_COLUMN_FIELD(UnsignedIntValue, unsigned_int_value)
SQT_COLUMN_FIELD(LongValue, long_value)
SQT_COLUMN_FIELD(UnsignedLongValue, unsigned_long_value)
SQT_COLUMN_FIELD(LongLongValue, long_long_value)
SQT_COLUMN_FIELD(UnsignedLongLongValue, unsigned_long_long_value)
SQT_COLUMN_FIELD(FloatValue, float_value)
SQT_COLUMN_FIELD(DoubleValue, double_value)
SQT_COLUMN_FIELD(StringValue, string_value)
SQT_TABLE_END
}

SQT_REGISTER(column_def_test::VariousValueEntity)

TEST(ColumnDefinitionTest, VariousValues) {

    using TableType = sqt::TableType<column_def_test::VariousValueEntity>;
    constexpr const auto& table = sqt::Table<column_def_test::VariousValueEntity>;

    {
        using BoolColumnType = TableType::ColumnType_BoolValue;
        static_assert(std::is_same_v<BoolColumnType::ValueType, bool>);
        static_assert(std::is_same_v<
            BoolColumnType::ValueTraits, 
            sqt::PrimitiveValueTraits<bool>>);
        constexpr const auto& bool_column = table.BoolValue;
        constexpr sqt::DataType data_type = bool_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = bool_column.IsNullable();
        ASSERT_EQ(is_nullable, false);
        ASSERT_EQ(bool_column.GetDefaultValueSQLLiteral(), std::nullopt);
    }

    {
        using CharColumnType = TableType::ColumnType_CharValue;
        static_assert(std::is_same_v<CharColumnType::ValueType, char>);
        static_assert(std::is_same_v<
            CharColumnType::ValueTraits,
            sqt::PrimitiveValueTraits<char>>);
        constexpr const auto& char_column = table.CharValue;
        constexpr sqt::DataType data_type = char_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = char_column.IsNullable();
        ASSERT_EQ(is_nullable, false);
        ASSERT_EQ(char_column.GetDefaultValueSQLLiteral(), std::nullopt);
    }

    {
        using SignedCharColumnType = TableType::ColumnType_SignedCharValue;
        static_assert(std::is_same_v<SignedCharColumnType::ValueType, signed char>);
        static_assert(std::is_same_v<
            SignedCharColumnType::ValueTraits,
            sqt::PrimitiveValueTraits<signed char>>);
        constexpr const auto& signed_char_column = table.SignedCharValue;
        constexpr sqt::DataType data_type = signed_char_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = signed_char_column.IsNullable();
        ASSERT_EQ(is_nullable, false);
        ASSERT_EQ(signed_char_column.GetDefaultValueSQLLiteral(), std::nullopt);
    }

    {
        using UnsignedCharColumnType = TableType::ColumnType_UnsignedCharValue;
        static_assert(std::is_same_v<UnsignedCharColumnType::ValueType, unsigned char>);
        static_assert(std::is_same_v<
            UnsignedCharColumnType::ValueTraits,
            sqt::PrimitiveValueTraits<unsigned char>>);
        constexpr const auto& unsigned_char_column = table.UnsignedCharValue;
        constexpr sqt::DataType data_type = unsigned_char_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = unsigned_char_column.IsNullable();
        ASSERT_EQ(is_nullable, false);
        ASSERT_EQ(unsigned_char_column.GetDefaultValueSQLLiteral(), std::nullopt);
    }

    {
        using Char8TColumnType = TableType::ColumnType_Char8TValue;
        static_assert(std::is_same_v<Char8TColumnType::ValueType, char8_t>);
        static_assert(std::is_same_v<
            Char8TColumnType::ValueTraits,
            sqt::PrimitiveValueTraits<char8_t>>);
        constexpr const auto& char8_t_column = table.Char8TValue;
        constexpr sqt::DataType data_type = char8_t_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = char8_t_column.IsNullable();
        ASSERT_EQ(is_nullable, false);
        ASSERT_EQ(char8_t_column.GetDefaultValueSQLLiteral(), std::nullopt);
    }

    {
        using Char16TColumnType = TableType::ColumnType_Char16TValue;
        static_assert(std::is_same_v<Char16TColumnType::ValueType, char16_t>);
        static_assert(std::is_same_v<
            Char16TColumnType::ValueTraits,
            sqt::PrimitiveValueTraits<char16_t>>);
        constexpr const auto& char16_t_column = table.Char16TValue;
        constexpr sqt::DataType data_type = char16_t_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = char16_t_column.IsNullable();
        ASSERT_EQ(is_nullable, false);
        ASSERT_EQ(char16_t_column.GetDefaultValueSQLLiteral(), std::nullopt);
    }

    {
        using Char32TColumnType = TableType::ColumnType_Char32TValue;
        static_assert(std::is_same_v<Char32TColumnType::ValueType, char32_t>);
        static_assert(std::is_same_v<
            Char32TColumnType::ValueTraits,
            sqt::PrimitiveValueTraits<char32_t>>);
        constexpr const auto& char32_t_column = table.Char32TValue;
        constexpr sqt::DataType data_type = char32_t_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = char32_t_column.IsNullable();
        ASSERT_EQ(is_nullable, false);
        ASSERT_EQ(char32_t_column.GetDefaultValueSQLLiteral(), std::nullopt);
    }

    {
        using WCharTColumnType = TableType::ColumnType_WCharTValue;
        static_assert(std::is_same_v<WCharTColumnType::ValueType, wchar_t>);
        static_assert(std::is_same_v<
            WCharTColumnType::ValueTraits,
            sqt::PrimitiveValueTraits<wchar_t>>);
        constexpr const auto& wchar_t_column = table.WCharTValue;
        constexpr sqt::DataType data_type = wchar_t_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = wchar_t_column.IsNullable();
        ASSERT_EQ(is_nullable, false);
        ASSERT_EQ(wchar_t_column.GetDefaultValueSQLLiteral(), std::nullopt);
    }

    {
        using ShortColumnType = TableType::ColumnType_ShortValue;
        static_assert(std::is_same_v<ShortColumnType::ValueType, short>);
        static_assert(std::is_same_v<
            ShortColumnType::ValueTraits,
            sqt::PrimitiveValueTraits<short>>);
        constexpr const auto& short_column = table.ShortValue;
        constexpr sqt::DataType data_type = short_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = short_column.IsNullable();
        ASSERT_EQ(is_nullable, false);
        ASSERT_EQ(short_column.GetDefaultValueSQLLiteral(), std::nullopt);
    }

    {
        using UnsignedShortColumnType = TableType::ColumnType_UnsignedShortValue;
        static_assert(std::is_same_v<UnsignedShortColumnType::ValueType, unsigned short>);
        static_assert(std::is_same_v<
            UnsignedShortColumnType::ValueTraits,
            sqt::PrimitiveValueTraits<unsigned short>>);
        constexpr const auto& unsigned_short_column = table.UnsignedShortValue;
        constexpr sqt::DataType data_type = unsigned_short_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = unsigned_short_column.IsNullable();
        ASSERT_EQ(is_nullable, false);
        ASSERT_EQ(unsigned_short_column.GetDefaultValueSQLLiteral(), std::nullopt);
    }

    {
        using IntColumnType = TableType::ColumnType_IntValue;
        static_assert(std::is_same_v<IntColumnType::ValueType, int>);
        static_assert(std::is_same_v<
            IntColumnType::ValueTraits,
            sqt::PrimitiveValueTraits<int>>);
        constexpr const auto& int_column = table.IntValue;
        constexpr sqt::DataType data_type = int_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = int_column.IsNullable();
        ASSERT_EQ(is_nullable, false);
        ASSERT_EQ(int_column.GetDefaultValueSQLLiteral(), std::nullopt);
    }

    {
        using UnsignedIntColumnType = TableType::ColumnType_UnsignedIntValue;
        static_assert(std::is_same_v<UnsignedIntColumnType::ValueType, unsigned int>);
        static_assert(std::is_same_v<
            UnsignedIntColumnType::ValueTraits,
            sqt::PrimitiveValueTraits<unsigned int>>);
        constexpr const auto& unsigned_int_column = table.UnsignedIntValue;
        constexpr sqt::DataType data_type = unsigned_int_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = unsigned_int_column.IsNullable();
        ASSERT_EQ(is_nullable, false);
        ASSERT_EQ(unsigned_int_column.GetDefaultValueSQLLiteral(), std::nullopt);
    }

    {
        using LongColumnType = TableType::ColumnType_LongValue;
        static_assert(std::is_same_v<LongColumnType::ValueType, long>);
        static_assert(std::is_same_v<
            LongColumnType::ValueTraits,
            sqt::PrimitiveValueTraits<long>>);
        constexpr const auto& long_column = table.LongValue;
        constexpr sqt::DataType data_type = long_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = long_column.IsNullable();
        ASSERT_EQ(is_nullable, false);
        ASSERT_EQ(long_column.GetDefaultValueSQLLiteral(), std::nullopt);
    }

    {
        using UnsignedLongColumnType = TableType::ColumnType_UnsignedLongValue;
        static_assert(std::is_same_v<UnsignedLongColumnType::ValueType, unsigned long>);
        static_assert(std::is_same_v<
            UnsignedLongColumnType::ValueTraits,
            sqt::PrimitiveValueTraits<unsigned long>>);
        constexpr const auto& unsigned_long_column = table.UnsignedLongValue;
        constexpr sqt::DataType data_type = unsigned_long_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = unsigned_long_column.IsNullable();
        ASSERT_EQ(is_nullable, false);
        ASSERT_EQ(unsigned_long_column.GetDefaultValueSQLLiteral(), std::nullopt);
    }

    {
        using LongLongColumnType = TableType::ColumnType_LongLongValue;
        static_assert(std::is_same_v<LongLongColumnType::ValueType, long long>);
        static_assert(std::is_same_v<
            LongLongColumnType::ValueTraits,
            sqt::PrimitiveValueTraits<long long>>);
        constexpr const auto& long_long_column = table.LongLongValue;
        constexpr sqt::DataType data_type = long_long_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = long_long_column.IsNullable();
        ASSERT_EQ(is_nullable, false);
        ASSERT_EQ(long_long_column.GetDefaultValueSQLLiteral(), std::nullopt);
    }

    {
        using UnsignedLongLongColumnType = TableType::ColumnType_UnsignedLongLongValue;
        static_assert(std::is_same_v<UnsignedLongLongColumnType::ValueType, unsigned long long>);
        static_assert(std::is_same_v<
            UnsignedLongLongColumnType::ValueTraits,
            sqt::PrimitiveValueTraits<unsigned long long>>);
        constexpr const auto& unsigned_long_long_column = table.UnsignedLongLongValue;
        constexpr sqt::DataType data_type = unsigned_long_long_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = unsigned_long_long_column.IsNullable();
        ASSERT_EQ(is_nullable, false);
        ASSERT_EQ(unsigned_long_long_column.GetDefaultValueSQLLiteral(), std::nullopt);
    }

    {
        using FloatColumnType = TableType::ColumnType_FloatValue;
        static_assert(std::is_same_v<FloatColumnType::ValueType, float>);
        static_assert(std::is_same_v<
            FloatColumnType::ValueTraits,
            sqt::PrimitiveValueTraits<float>>);
        constexpr const auto& float_column = table.FloatValue;
        constexpr sqt::DataType data_type = float_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Float);
        constexpr bool is_nullable = float_column.IsNullable();
        ASSERT_EQ(is_nullable, false);
        ASSERT_EQ(float_column.GetDefaultValueSQLLiteral(), std::nullopt);
    }

    {
        using DoubleColumnType = TableType::ColumnType_DoubleValue;
        static_assert(std::is_same_v<DoubleColumnType::ValueType, double>);
        static_assert(std::is_same_v<
            DoubleColumnType::ValueTraits,
            sqt::PrimitiveValueTraits<double>>);
        constexpr const auto& double_column = table.DoubleValue;
        constexpr sqt::DataType data_type = double_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Float);
        constexpr bool is_nullable = double_column.IsNullable();
        ASSERT_EQ(is_nullable, false);
        ASSERT_EQ(double_column.GetDefaultValueSQLLiteral(), std::nullopt);
    }

    {
        using StringColumnType = TableType::ColumnType_StringValue;
        static_assert(std::is_same_v<StringColumnType::ValueType, std::string>);
        static_assert(std::is_same_v<
            StringColumnType::ValueTraits,
            sqt::PrimitiveValueTraits<std::string>>);
        constexpr const auto& string_column = table.StringValue;
        constexpr sqt::DataType data_type = string_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Text);
        constexpr bool is_nullable = string_column.IsNullable();
        ASSERT_EQ(is_nullable, false);
        ASSERT_EQ(string_column.GetDefaultValueSQLLiteral(), std::nullopt);
    }
}


namespace column_def_test {
struct VariousValueDefaultEntity {
    bool bool_value{};
    char char_value{};
    signed char signed_char_value{};
    unsigned char unsigned_char_value{};
    char8_t char8_t_value{};
    char16_t char16_t_value{};
    char32_t char32_t_value{};
    wchar_t wchar_t_value{};
    short short_value{};
    unsigned short unsigned_short_value{};
    int int_value{};
    unsigned int unsigned_int_value{};
    long long_value{};
    unsigned long unsigned_long_value{};
    long long long_long_value{};
    unsigned long long unsigned_long_long_value{};
    float float_value{};
    double double_value{};
    std::string string_value;
};
SQT_TABLE_BEGIN(VariousValueDefaultEntity, VariousValueDefaultEntity)
SQT_COLUMN_FIELD_DEFAULT(BoolValue, bool_value, true)
SQT_COLUMN_FIELD_DEFAULT(CharValue, char_value, 'A')
SQT_COLUMN_FIELD_DEFAULT(SignedCharValue, signed_char_value, -12)
SQT_COLUMN_FIELD_DEFAULT(UnsignedCharValue, unsigned_char_value, 250)
SQT_COLUMN_FIELD_DEFAULT(Char8TValue, char8_t_value, u8'Z')
SQT_COLUMN_FIELD_DEFAULT(Char16TValue, char16_t_value, u'\u4E2D')
SQT_COLUMN_FIELD_DEFAULT(Char32TValue, char32_t_value, U'\U0001F600')
SQT_COLUMN_FIELD_DEFAULT(WCharTValue, wchar_t_value, L'X')
SQT_COLUMN_FIELD_DEFAULT(ShortValue, short_value, -32123)
SQT_COLUMN_FIELD_DEFAULT(UnsignedShortValue, unsigned_short_value, 54321)
SQT_COLUMN_FIELD_DEFAULT(IntValue, int_value, 42)
SQT_COLUMN_FIELD_DEFAULT(UnsignedIntValue, unsigned_int_value, 4000000000u)
SQT_COLUMN_FIELD_DEFAULT(LongValue, long_value, -123456789l)
SQT_COLUMN_FIELD_DEFAULT(UnsignedLongValue, unsigned_long_value, 123456789ul)
SQT_COLUMN_FIELD_DEFAULT(LongLongValue, long_long_value, -1234567890123ll)
SQT_COLUMN_FIELD_DEFAULT(UnsignedLongLongValue, unsigned_long_long_value, 1234567890123ull)
SQT_COLUMN_FIELD_DEFAULT(FloatValue, float_value, 3.14f)
SQT_COLUMN_FIELD_DEFAULT(DoubleValue, double_value, 3.1415926)
SQT_COLUMN_FIELD_DEFAULT(StringValue, string_value, "Hello")
SQT_TABLE_END
}

SQT_REGISTER(column_def_test::VariousValueDefaultEntity)

TEST(ColumnDefinitionTest, VariousValuesDefault) {

    using TableType = sqt::TableType<column_def_test::VariousValueDefaultEntity>;
    constexpr const auto& table = sqt::Table<column_def_test::VariousValueDefaultEntity>;

    {
        using BoolColumnType = TableType::ColumnType_BoolValue;
        static_assert(std::is_same_v<BoolColumnType::ValueType, bool>);
        static_assert(std::is_same_v<
            BoolColumnType::ValueTraits,
            sqt::PrimitiveValueTraits<bool>>);
        static_assert(std::is_same_v<typename BoolColumnType::DefaultValueType, bool>);
        static_assert((BoolColumnType::DefaultValue == true));
        constexpr const auto& bool_column = table.BoolValue;
        constexpr sqt::DataType data_type = bool_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = bool_column.IsNullable();
        ASSERT_EQ(is_nullable, false);
        ASSERT_EQ(bool_column.GetDefaultValueSQLLiteral(), "1");
    }

    {
        using CharColumnType = TableType::ColumnType_CharValue;
        static_assert(std::is_same_v<CharColumnType::ValueType, char>);
        static_assert(std::is_same_v<
            CharColumnType::ValueTraits,
            sqt::PrimitiveValueTraits<char>>);
        static_assert(std::is_same_v<typename CharColumnType::DefaultValueType, char>);
        static_assert((CharColumnType::DefaultValue == 'A'));
        constexpr const auto& char_column = table.CharValue;
        constexpr sqt::DataType data_type = char_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = char_column.IsNullable();
        ASSERT_EQ(is_nullable, false);
        ASSERT_EQ(char_column.GetDefaultValueSQLLiteral(), "65");
    }

    {
        using SignedCharColumnType = TableType::ColumnType_SignedCharValue;
        static_assert(std::is_same_v<SignedCharColumnType::ValueType, signed char>);
        static_assert(std::is_same_v<
            SignedCharColumnType::ValueTraits,
            sqt::PrimitiveValueTraits<signed char>>);
        static_assert(std::is_same_v<
            typename SignedCharColumnType::DefaultValueType,
            signed char>);
        static_assert((SignedCharColumnType::DefaultValue == static_cast<signed char>(-12)));
        constexpr const auto& signed_char_column = table.SignedCharValue;
        constexpr sqt::DataType data_type = signed_char_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = signed_char_column.IsNullable();
        ASSERT_EQ(is_nullable, false);
        ASSERT_EQ(signed_char_column.GetDefaultValueSQLLiteral(), "-12");
    }

    {
        using UnsignedCharColumnType = TableType::ColumnType_UnsignedCharValue;
        static_assert(std::is_same_v<UnsignedCharColumnType::ValueType, unsigned char>);
        static_assert(std::is_same_v<
            UnsignedCharColumnType::ValueTraits,
            sqt::PrimitiveValueTraits<unsigned char>>);
        static_assert(std::is_same_v<
            typename UnsignedCharColumnType::DefaultValueType,
            unsigned char>);
        static_assert((UnsignedCharColumnType::DefaultValue == static_cast<unsigned char>(250)));
        constexpr const auto& unsigned_char_column = table.UnsignedCharValue;
        constexpr sqt::DataType data_type = unsigned_char_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = unsigned_char_column.IsNullable();
        ASSERT_EQ(is_nullable, false);
        ASSERT_EQ(unsigned_char_column.GetDefaultValueSQLLiteral(), "250");
    }

    {
        using Char8TColumnType = TableType::ColumnType_Char8TValue;
        static_assert(std::is_same_v<Char8TColumnType::ValueType, char8_t>);
        static_assert(std::is_same_v<
            Char8TColumnType::ValueTraits,
            sqt::PrimitiveValueTraits<char8_t>>);
        static_assert(std::is_same_v<typename Char8TColumnType::DefaultValueType, char8_t>);
        static_assert((Char8TColumnType::DefaultValue == u8'Z'));
        constexpr const auto& char8_t_column = table.Char8TValue;
        constexpr sqt::DataType data_type = char8_t_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = char8_t_column.IsNullable();
        ASSERT_EQ(is_nullable, false);
        ASSERT_EQ(char8_t_column.GetDefaultValueSQLLiteral(), "90");
    }

    {
        using Char16TColumnType = TableType::ColumnType_Char16TValue;
        static_assert(std::is_same_v<Char16TColumnType::ValueType, char16_t>);
        static_assert(std::is_same_v<
            Char16TColumnType::ValueTraits,
            sqt::PrimitiveValueTraits<char16_t>>);
        static_assert(std::is_same_v<typename Char16TColumnType::DefaultValueType, char16_t>);
        static_assert((Char16TColumnType::DefaultValue == u'\u4E2D'));
        constexpr const auto& char16_t_column = table.Char16TValue;
        constexpr sqt::DataType data_type = char16_t_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = char16_t_column.IsNullable();
        ASSERT_EQ(is_nullable, false);
        ASSERT_EQ(char16_t_column.GetDefaultValueSQLLiteral(), "20013");
    }

    {
        using Char32TColumnType = TableType::ColumnType_Char32TValue;
        static_assert(std::is_same_v<Char32TColumnType::ValueType, char32_t>);
        static_assert(std::is_same_v<
            Char32TColumnType::ValueTraits,
            sqt::PrimitiveValueTraits<char32_t>>);
        static_assert(std::is_same_v<typename Char32TColumnType::DefaultValueType, char32_t>);
        static_assert((Char32TColumnType::DefaultValue == U'\U0001F600'));
        constexpr const auto& char32_t_column = table.Char32TValue;
        constexpr sqt::DataType data_type = char32_t_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = char32_t_column.IsNullable();
        ASSERT_EQ(is_nullable, false);
        ASSERT_EQ(char32_t_column.GetDefaultValueSQLLiteral(), "128512");
    }

    {
        using WCharTColumnType = TableType::ColumnType_WCharTValue;
        static_assert(std::is_same_v<WCharTColumnType::ValueType, wchar_t>);
        static_assert(std::is_same_v<
            WCharTColumnType::ValueTraits,
            sqt::PrimitiveValueTraits<wchar_t>>);
        static_assert(std::is_same_v<typename WCharTColumnType::DefaultValueType, wchar_t>);
        static_assert((WCharTColumnType::DefaultValue == L'X'));
        constexpr const auto& wchar_t_column = table.WCharTValue;
        constexpr sqt::DataType data_type = wchar_t_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = wchar_t_column.IsNullable();
        ASSERT_EQ(is_nullable, false);
        ASSERT_EQ(wchar_t_column.GetDefaultValueSQLLiteral(), "88");
    }

    {
        using ShortColumnType = TableType::ColumnType_ShortValue;
        static_assert(std::is_same_v<ShortColumnType::ValueType, short>);
        static_assert(std::is_same_v<
            ShortColumnType::ValueTraits,
            sqt::PrimitiveValueTraits<short>>);
        static_assert(std::is_same_v<typename ShortColumnType::DefaultValueType, short>);
        static_assert((ShortColumnType::DefaultValue == static_cast<short>(-32123)));
        constexpr const auto& short_column = table.ShortValue;
        constexpr sqt::DataType data_type = short_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = short_column.IsNullable();
        ASSERT_EQ(is_nullable, false);
        ASSERT_EQ(short_column.GetDefaultValueSQLLiteral(), "-32123");
    }

    {
        using UnsignedShortColumnType = TableType::ColumnType_UnsignedShortValue;
        static_assert(std::is_same_v<UnsignedShortColumnType::ValueType, unsigned short>);
        static_assert(std::is_same_v<
            UnsignedShortColumnType::ValueTraits,
            sqt::PrimitiveValueTraits<unsigned short>>);
        static_assert(std::is_same_v<
            typename UnsignedShortColumnType::DefaultValueType,
            unsigned short>);
        static_assert((
            UnsignedShortColumnType::DefaultValue == static_cast<unsigned short>(54321)));
        constexpr const auto& unsigned_short_column = table.UnsignedShortValue;
        constexpr sqt::DataType data_type = unsigned_short_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = unsigned_short_column.IsNullable();
        ASSERT_EQ(is_nullable, false);
        ASSERT_EQ(unsigned_short_column.GetDefaultValueSQLLiteral(), "54321");
    }

    {
        using IntColumnType = TableType::ColumnType_IntValue;
        static_assert(std::is_same_v<IntColumnType::ValueType, int>);
        static_assert(std::is_same_v<
            IntColumnType::ValueTraits,
            sqt::PrimitiveValueTraits<int>>);
        static_assert(std::is_same_v<typename IntColumnType::DefaultValueType, int>);
        static_assert((IntColumnType::DefaultValue == 42));
        constexpr const auto& int_column = table.IntValue;
        constexpr sqt::DataType data_type = int_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = int_column.IsNullable();
        ASSERT_EQ(is_nullable, false);
        ASSERT_EQ(int_column.GetDefaultValueSQLLiteral(), "42");
    }

    {
        using UnsignedIntColumnType = TableType::ColumnType_UnsignedIntValue;
        static_assert(std::is_same_v<UnsignedIntColumnType::ValueType, unsigned int>);
        static_assert(std::is_same_v<
            UnsignedIntColumnType::ValueTraits,
            sqt::PrimitiveValueTraits<unsigned int>>);
        static_assert(std::is_same_v<
            typename UnsignedIntColumnType::DefaultValueType,
            unsigned int>);
        static_assert((UnsignedIntColumnType::DefaultValue == 4000000000u));
        constexpr const auto& unsigned_int_column = table.UnsignedIntValue;
        constexpr sqt::DataType data_type = unsigned_int_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = unsigned_int_column.IsNullable();
        ASSERT_EQ(is_nullable, false);
        ASSERT_EQ(unsigned_int_column.GetDefaultValueSQLLiteral(), "4000000000");
    }

    {
        using LongColumnType = TableType::ColumnType_LongValue;
        static_assert(std::is_same_v<LongColumnType::ValueType, long>);
        static_assert(std::is_same_v<
            LongColumnType::ValueTraits,
            sqt::PrimitiveValueTraits<long>>);
        static_assert(std::is_same_v<typename LongColumnType::DefaultValueType, long>);
        static_assert((LongColumnType::DefaultValue == -123456789l));
        constexpr const auto& long_column = table.LongValue;
        constexpr sqt::DataType data_type = long_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = long_column.IsNullable();
        ASSERT_EQ(is_nullable, false);
        ASSERT_EQ(long_column.GetDefaultValueSQLLiteral(), "-123456789");
    }

    {
        using UnsignedLongColumnType = TableType::ColumnType_UnsignedLongValue;
        static_assert(std::is_same_v<UnsignedLongColumnType::ValueType, unsigned long>);
        static_assert(std::is_same_v<
            UnsignedLongColumnType::ValueTraits,
            sqt::PrimitiveValueTraits<unsigned long>>);
        static_assert(std::is_same_v<
            typename UnsignedLongColumnType::DefaultValueType,
            unsigned long>);
        static_assert((UnsignedLongColumnType::DefaultValue == 123456789ul));
        constexpr const auto& unsigned_long_column = table.UnsignedLongValue;
        constexpr sqt::DataType data_type = unsigned_long_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = unsigned_long_column.IsNullable();
        ASSERT_EQ(is_nullable, false);
        ASSERT_EQ(unsigned_long_column.GetDefaultValueSQLLiteral(), "123456789");
    }

    {
        using LongLongColumnType = TableType::ColumnType_LongLongValue;
        static_assert(std::is_same_v<LongLongColumnType::ValueType, long long>);
        static_assert(std::is_same_v<
            LongLongColumnType::ValueTraits,
            sqt::PrimitiveValueTraits<long long>>);
        static_assert(std::is_same_v<typename LongLongColumnType::DefaultValueType, long long>);
        static_assert((LongLongColumnType::DefaultValue == -1234567890123ll));
        constexpr const auto& long_long_column = table.LongLongValue;
        constexpr sqt::DataType data_type = long_long_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = long_long_column.IsNullable();
        ASSERT_EQ(is_nullable, false);
        ASSERT_EQ(long_long_column.GetDefaultValueSQLLiteral(), "-1234567890123");
    }

    {
        using UnsignedLongLongColumnType = TableType::ColumnType_UnsignedLongLongValue;
        static_assert(std::is_same_v<UnsignedLongLongColumnType::ValueType, unsigned long long>);
        static_assert(std::is_same_v<
            UnsignedLongLongColumnType::ValueTraits,
            sqt::PrimitiveValueTraits<unsigned long long>>);
        static_assert(std::is_same_v<
            typename UnsignedLongLongColumnType::DefaultValueType,
            unsigned long long>);
        static_assert((UnsignedLongLongColumnType::DefaultValue == 1234567890123ull));
        constexpr const auto& unsigned_long_long_column = table.UnsignedLongLongValue;
        constexpr sqt::DataType data_type = unsigned_long_long_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = unsigned_long_long_column.IsNullable();
        ASSERT_EQ(is_nullable, false);
        ASSERT_EQ(unsigned_long_long_column.GetDefaultValueSQLLiteral(), "1234567890123");
    }

    {
        using FloatColumnType = TableType::ColumnType_FloatValue;
        static_assert(std::is_same_v<FloatColumnType::ValueType, float>);
        static_assert(std::is_same_v<
            FloatColumnType::ValueTraits,
            sqt::PrimitiveValueTraits<float>>);
        static_assert(std::is_same_v<typename FloatColumnType::DefaultValueType, float>);
        static_assert((FloatColumnType::DefaultValue == 3.14f));
        constexpr const auto& float_column = table.FloatValue;
        constexpr sqt::DataType data_type = float_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Float);
        constexpr bool is_nullable = float_column.IsNullable();
        ASSERT_EQ(is_nullable, false);
        ASSERT_EQ(float_column.GetDefaultValueSQLLiteral(), "3.140000");
    }

    {
        using DoubleColumnType = TableType::ColumnType_DoubleValue;
        static_assert(std::is_same_v<DoubleColumnType::ValueType, double>);
        static_assert(std::is_same_v<
            DoubleColumnType::ValueTraits,
            sqt::PrimitiveValueTraits<double>>);
        static_assert(std::is_same_v<typename DoubleColumnType::DefaultValueType, double>);
        static_assert((DoubleColumnType::DefaultValue == 3.1415926));
        constexpr const auto& double_column = table.DoubleValue;
        constexpr sqt::DataType data_type = double_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Float);
        constexpr bool is_nullable = double_column.IsNullable();
        ASSERT_EQ(is_nullable, false);
        ASSERT_EQ(double_column.GetDefaultValueSQLLiteral(), "3.141593");
    }

    {
        using StringColumnType = TableType::ColumnType_StringValue;
        static_assert(std::is_same_v<StringColumnType::ValueType, std::string>);
        static_assert(std::is_same_v<
            StringColumnType::ValueTraits,
            sqt::PrimitiveValueTraits<std::string>>);
        static_assert(std::is_same_v<
            typename StringColumnType::DefaultValueType,
            std::string_view>);
        static_assert((StringColumnType::DefaultValue == std::string_view{"Hello"}));
        constexpr const auto& string_column = table.StringValue;
        constexpr sqt::DataType data_type = string_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Text);
        constexpr bool is_nullable = string_column.IsNullable();
        ASSERT_EQ(is_nullable, false);
        ASSERT_EQ(string_column.GetDefaultValueSQLLiteral(), "'Hello'");
    }
}


namespace column_def_test {
struct NullableValueDefaultEntity {
    std::optional<bool> bool_value;
    std::optional<char> char_value;
    std::optional<signed char> signed_char_value;
    std::optional<unsigned char> unsigned_char_value;
    std::optional<char8_t> char8_t_value;
    std::optional<char16_t> char16_t_value;
    std::optional<char32_t> char32_t_value;
    std::optional<wchar_t> wchar_t_value;
    std::optional<short> short_value;
    std::optional<unsigned short> unsigned_short_value;
    std::optional<int> int_value;
    std::optional<unsigned int> unsigned_int_value;
    std::optional<long> long_value;
    std::optional<unsigned long> unsigned_long_value;
    std::optional<long long> long_long_value;
    std::optional<unsigned long long> unsigned_long_long_value;
    std::optional<float> float_value;
    std::optional<double> double_value;
    std::optional<std::string> string_value;
};
SQT_TABLE_BEGIN(NullableValueDefaultEntity, NullableValueDefaultEntity)
SQT_COLUMN_FIELD_DEFAULT(BoolValue, bool_value, true)
SQT_COLUMN_FIELD_DEFAULT(CharValue, char_value, 'A')
SQT_COLUMN_FIELD_DEFAULT(SignedCharValue, signed_char_value, -12)
SQT_COLUMN_FIELD_DEFAULT(UnsignedCharValue, unsigned_char_value, 250)
SQT_COLUMN_FIELD_DEFAULT(Char8TValue, char8_t_value, u8'Z')
SQT_COLUMN_FIELD_DEFAULT(Char16TValue, char16_t_value, u'\u4E2D')
SQT_COLUMN_FIELD_DEFAULT(Char32TValue, char32_t_value, U'\U0001F600')
SQT_COLUMN_FIELD_DEFAULT(WCharTValue, wchar_t_value, L'X')
SQT_COLUMN_FIELD_DEFAULT(ShortValue, short_value, -32123)
SQT_COLUMN_FIELD_DEFAULT(UnsignedShortValue, unsigned_short_value, 54321)
SQT_COLUMN_FIELD_DEFAULT(IntValue, int_value, 42)
SQT_COLUMN_FIELD_DEFAULT(UnsignedIntValue, unsigned_int_value, 4000000000u)
SQT_COLUMN_FIELD_DEFAULT(LongValue, long_value, -123456789l)
SQT_COLUMN_FIELD_DEFAULT(UnsignedLongValue, unsigned_long_value, 123456789ul)
SQT_COLUMN_FIELD_DEFAULT(LongLongValue, long_long_value, -1234567890123ll)
SQT_COLUMN_FIELD_DEFAULT(UnsignedLongLongValue, unsigned_long_long_value, 1234567890123ull)
SQT_COLUMN_FIELD_DEFAULT(FloatValue, float_value, 3.14f)
SQT_COLUMN_FIELD_DEFAULT(DoubleValue, double_value, 3.1415926)
SQT_COLUMN_FIELD_DEFAULT(StringValue, string_value, "Hello")
SQT_TABLE_END
}

SQT_REGISTER(column_def_test::NullableValueDefaultEntity)

TEST(ColumnDefinitionTest, NullableValuesDefault) {

    using TableType = sqt::TableType<column_def_test::NullableValueDefaultEntity>;
    constexpr const auto& table = sqt::Table<column_def_test::NullableValueDefaultEntity>;

    {
        using BoolColumnType = TableType::ColumnType_BoolValue;
        static_assert(std::is_same_v<BoolColumnType::ValueType, std::optional<bool>>);
        static_assert(std::is_same_v<
            BoolColumnType::ValueTraits,
            sqt::NullableValueTraits<std::optional<bool>>>);
        static_assert(std::is_same_v<
            typename BoolColumnType::DefaultValueType,
            std::optional<bool>>);
        static_assert((BoolColumnType::DefaultValue == std::optional<bool>{true}));
        constexpr const auto& bool_column = table.BoolValue;
        constexpr sqt::DataType data_type = bool_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = bool_column.IsNullable();
        ASSERT_EQ(is_nullable, true);
        ASSERT_EQ(bool_column.GetDefaultValueSQLLiteral(), "1");
    }

    {
        using CharColumnType = TableType::ColumnType_CharValue;
        static_assert(std::is_same_v<CharColumnType::ValueType, std::optional<char>>);
        static_assert(std::is_same_v<
            CharColumnType::ValueTraits,
            sqt::NullableValueTraits<std::optional<char>>>);
        static_assert(std::is_same_v<
            typename CharColumnType::DefaultValueType,
            std::optional<char>>);
        static_assert((CharColumnType::DefaultValue == std::optional<char>{'A'}));
        constexpr const auto& char_column = table.CharValue;
        constexpr sqt::DataType data_type = char_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = char_column.IsNullable();
        ASSERT_EQ(is_nullable, true);
        ASSERT_EQ(char_column.GetDefaultValueSQLLiteral(), "65");
    }

    {
        using SignedCharColumnType = TableType::ColumnType_SignedCharValue;
        static_assert(std::is_same_v<
            SignedCharColumnType::ValueType,
            std::optional<signed char>>);
        static_assert(std::is_same_v<
            SignedCharColumnType::ValueTraits,
            sqt::NullableValueTraits<std::optional<signed char>>>);
        static_assert(std::is_same_v<
            typename SignedCharColumnType::DefaultValueType,
            std::optional<signed char>>);
        static_assert((
            SignedCharColumnType::DefaultValue ==
            std::optional<signed char>{ static_cast<signed char>(-12) }));
        constexpr const auto& signed_char_column = table.SignedCharValue;
        constexpr sqt::DataType data_type = signed_char_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = signed_char_column.IsNullable();
        ASSERT_EQ(is_nullable, true);
        ASSERT_EQ(signed_char_column.GetDefaultValueSQLLiteral(), "-12");
    }

    {
        using UnsignedCharColumnType = TableType::ColumnType_UnsignedCharValue;
        static_assert(std::is_same_v<
            UnsignedCharColumnType::ValueType,
            std::optional<unsigned char>>);
        static_assert(std::is_same_v<
            UnsignedCharColumnType::ValueTraits,
            sqt::NullableValueTraits<std::optional<unsigned char>>>);
        static_assert(std::is_same_v<
            typename UnsignedCharColumnType::DefaultValueType,
            std::optional<unsigned char>>);
        static_assert((
            UnsignedCharColumnType::DefaultValue ==
            std::optional<unsigned char>{ static_cast<unsigned char>(250) }));
        constexpr const auto& unsigned_char_column = table.UnsignedCharValue;
        constexpr sqt::DataType data_type = unsigned_char_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = unsigned_char_column.IsNullable();
        ASSERT_EQ(is_nullable, true);
        ASSERT_EQ(unsigned_char_column.GetDefaultValueSQLLiteral(), "250");
    }

    {
        using Char8TColumnType = TableType::ColumnType_Char8TValue;
        static_assert(std::is_same_v<
            Char8TColumnType::ValueType,
            std::optional<char8_t>>);
        static_assert(std::is_same_v<
            Char8TColumnType::ValueTraits,
            sqt::NullableValueTraits<std::optional<char8_t>>>);
        static_assert(std::is_same_v<
            typename Char8TColumnType::DefaultValueType,
            std::optional<char8_t>>);
        static_assert((Char8TColumnType::DefaultValue == std::optional<char8_t>{ u8'Z' }));
        constexpr const auto& char8_t_column = table.Char8TValue;
        constexpr sqt::DataType data_type = char8_t_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = char8_t_column.IsNullable();
        ASSERT_EQ(is_nullable, true);
        ASSERT_EQ(char8_t_column.GetDefaultValueSQLLiteral(), "90");
    }

    {
        using Char16TColumnType = TableType::ColumnType_Char16TValue;
        static_assert(std::is_same_v<
            Char16TColumnType::ValueType,
            std::optional<char16_t>>);
        static_assert(std::is_same_v<
            Char16TColumnType::ValueTraits,
            sqt::NullableValueTraits<std::optional<char16_t>>>);
        static_assert(std::is_same_v<
            typename Char16TColumnType::DefaultValueType,
            std::optional<char16_t>>);
        static_assert((
            Char16TColumnType::DefaultValue == std::optional<char16_t>{ u'\u4E2D' }));
        constexpr const auto& char16_t_column = table.Char16TValue;
        constexpr sqt::DataType data_type = char16_t_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = char16_t_column.IsNullable();
        ASSERT_EQ(is_nullable, true);
        ASSERT_EQ(char16_t_column.GetDefaultValueSQLLiteral(), "20013");
    }

    {
        using Char32TColumnType = TableType::ColumnType_Char32TValue;
        static_assert(std::is_same_v<
            Char32TColumnType::ValueType,
            std::optional<char32_t>>);
        static_assert(std::is_same_v<
            Char32TColumnType::ValueTraits,
            sqt::NullableValueTraits<std::optional<char32_t>>>);
        static_assert(std::is_same_v<
            typename Char32TColumnType::DefaultValueType,
            std::optional<char32_t>>);
        static_assert((
            Char32TColumnType::DefaultValue ==
            std::optional<char32_t>{ U'\U0001F600' }));
        constexpr const auto& char32_t_column = table.Char32TValue;
        constexpr sqt::DataType data_type = char32_t_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = char32_t_column.IsNullable();
        ASSERT_EQ(is_nullable, true);
        ASSERT_EQ(char32_t_column.GetDefaultValueSQLLiteral(), "128512");
    }

    {
        using WCharTColumnType = TableType::ColumnType_WCharTValue;
        static_assert(std::is_same_v<
            WCharTColumnType::ValueType,
            std::optional<wchar_t>>);
        static_assert(std::is_same_v<
            WCharTColumnType::ValueTraits,
            sqt::NullableValueTraits<std::optional<wchar_t>>>);
        static_assert(std::is_same_v<
            typename WCharTColumnType::DefaultValueType,
            std::optional<wchar_t>>);
        static_assert((WCharTColumnType::DefaultValue == std::optional<wchar_t>{ L'X' }));
        constexpr const auto& wchar_t_column = table.WCharTValue;
        constexpr sqt::DataType data_type = wchar_t_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = wchar_t_column.IsNullable();
        ASSERT_EQ(is_nullable, true);
        ASSERT_EQ(wchar_t_column.GetDefaultValueSQLLiteral(), "88");
    }

    {
        using ShortColumnType = TableType::ColumnType_ShortValue;
        static_assert(std::is_same_v<
            ShortColumnType::ValueType,
            std::optional<short>>);
        static_assert(std::is_same_v<
            ShortColumnType::ValueTraits,
            sqt::NullableValueTraits<std::optional<short>>>);
        static_assert(std::is_same_v<
            typename ShortColumnType::DefaultValueType,
            std::optional<short>>);
        static_assert((
            ShortColumnType::DefaultValue == std::optional<short>{ static_cast<short>(-32123) }));
        constexpr const auto& short_column = table.ShortValue;
        constexpr sqt::DataType data_type = short_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = short_column.IsNullable();
        ASSERT_EQ(is_nullable, true);
        ASSERT_EQ(short_column.GetDefaultValueSQLLiteral(), "-32123");
    }

    {
        using UnsignedShortColumnType = TableType::ColumnType_UnsignedShortValue;
        static_assert(std::is_same_v<
            UnsignedShortColumnType::ValueType,
            std::optional<unsigned short>>);
        static_assert(std::is_same_v<
            UnsignedShortColumnType::ValueTraits,
            sqt::NullableValueTraits<std::optional<unsigned short>>>);
        static_assert(std::is_same_v<
            typename UnsignedShortColumnType::DefaultValueType,
            std::optional<unsigned short>>);
        static_assert((
            UnsignedShortColumnType::DefaultValue ==
            std::optional<unsigned short>{ static_cast<unsigned short>(54321) }));
        constexpr const auto& unsigned_short_column = table.UnsignedShortValue;
        constexpr sqt::DataType data_type = unsigned_short_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = unsigned_short_column.IsNullable();
        ASSERT_EQ(is_nullable, true);
        ASSERT_EQ(unsigned_short_column.GetDefaultValueSQLLiteral(), "54321");
    }

    {
        using IntColumnType = TableType::ColumnType_IntValue;
        static_assert(std::is_same_v<
            IntColumnType::ValueType,
            std::optional<int>>);
        static_assert(std::is_same_v<
            IntColumnType::ValueTraits,
            sqt::NullableValueTraits<std::optional<int>>>);
        static_assert(std::is_same_v<
            typename IntColumnType::DefaultValueType,
            std::optional<int>>);
        static_assert((IntColumnType::DefaultValue == std::optional<int>{ 42 }));
        constexpr const auto& int_column = table.IntValue;
        constexpr sqt::DataType data_type = int_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = int_column.IsNullable();
        ASSERT_EQ(is_nullable, true);
        ASSERT_EQ(int_column.GetDefaultValueSQLLiteral(), "42");
    }

    {
        using UnsignedIntColumnType = TableType::ColumnType_UnsignedIntValue;
        static_assert(std::is_same_v<
            UnsignedIntColumnType::ValueType,
            std::optional<unsigned int>>);
        static_assert(std::is_same_v<
            UnsignedIntColumnType::ValueTraits,
            sqt::NullableValueTraits<std::optional<unsigned int>>>);
        static_assert(std::is_same_v<
            typename UnsignedIntColumnType::DefaultValueType,
            std::optional<unsigned int>>);
        static_assert((
            UnsignedIntColumnType::DefaultValue == std::optional<unsigned int>{ 4000000000u }));
        constexpr const auto& unsigned_int_column = table.UnsignedIntValue;
        constexpr sqt::DataType data_type = unsigned_int_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = unsigned_int_column.IsNullable();
        ASSERT_EQ(is_nullable, true);
        ASSERT_EQ(unsigned_int_column.GetDefaultValueSQLLiteral(), "4000000000");
    }

    {
        using LongColumnType = TableType::ColumnType_LongValue;
        static_assert(std::is_same_v<
            LongColumnType::ValueType,
            std::optional<long>>);
        static_assert(std::is_same_v<
            LongColumnType::ValueTraits,
            sqt::NullableValueTraits<std::optional<long>>>);
        static_assert(std::is_same_v<
            typename LongColumnType::DefaultValueType,
            std::optional<long>>);
        static_assert((LongColumnType::DefaultValue == std::optional<long>{ -123456789l }));
        constexpr const auto& long_column = table.LongValue;
        constexpr sqt::DataType data_type = long_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = long_column.IsNullable();
        ASSERT_EQ(is_nullable, true);
        ASSERT_EQ(long_column.GetDefaultValueSQLLiteral(), "-123456789");
    }

    {
        using UnsignedLongColumnType = TableType::ColumnType_UnsignedLongValue;
        static_assert(std::is_same_v<
            UnsignedLongColumnType::ValueType,
            std::optional<unsigned long>>);
        static_assert(std::is_same_v<
            UnsignedLongColumnType::ValueTraits,
            sqt::NullableValueTraits<std::optional<unsigned long>>>);
        static_assert(std::is_same_v<
            typename UnsignedLongColumnType::DefaultValueType,
            std::optional<unsigned long>>);
        static_assert((
            UnsignedLongColumnType::DefaultValue == std::optional<unsigned long>{ 123456789ul }));
        constexpr const auto& unsigned_long_column = table.UnsignedLongValue;
        constexpr sqt::DataType data_type = unsigned_long_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = unsigned_long_column.IsNullable();
        ASSERT_EQ(is_nullable, true);
        ASSERT_EQ(unsigned_long_column.GetDefaultValueSQLLiteral(), "123456789");
    }

    {
        using LongLongColumnType = TableType::ColumnType_LongLongValue;
        static_assert(std::is_same_v<
            LongLongColumnType::ValueType,
            std::optional<long long>>);
        static_assert(std::is_same_v<
            LongLongColumnType::ValueTraits,
            sqt::NullableValueTraits<std::optional<long long>>>);
        static_assert(std::is_same_v<
            typename LongLongColumnType::DefaultValueType,
            std::optional<long long>>);
        static_assert((
            LongLongColumnType::DefaultValue == std::optional<long long>{ -1234567890123ll }));
        constexpr const auto& long_long_column = table.LongLongValue;
        constexpr sqt::DataType data_type = long_long_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = long_long_column.IsNullable();
        ASSERT_EQ(is_nullable, true);
        ASSERT_EQ(long_long_column.GetDefaultValueSQLLiteral(), "-1234567890123");
    }

    {
        using UnsignedLongLongColumnType = TableType::ColumnType_UnsignedLongLongValue;
        static_assert(std::is_same_v<
            UnsignedLongLongColumnType::ValueType,
            std::optional<unsigned long long>>);
        static_assert(std::is_same_v<
            UnsignedLongLongColumnType::ValueTraits,
            sqt::NullableValueTraits<std::optional<unsigned long long>>>);
        static_assert(std::is_same_v<
            typename UnsignedLongLongColumnType::DefaultValueType,
            std::optional<unsigned long long>>);
        static_assert((
            UnsignedLongLongColumnType::DefaultValue ==
            std::optional<unsigned long long>{ 1234567890123ull }));
        constexpr const auto& unsigned_long_long_column = table.UnsignedLongLongValue;
        constexpr sqt::DataType data_type = unsigned_long_long_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = unsigned_long_long_column.IsNullable();
        ASSERT_EQ(is_nullable, true);
        ASSERT_EQ(unsigned_long_long_column.GetDefaultValueSQLLiteral(), "1234567890123");
    }

    {
        using FloatColumnType = TableType::ColumnType_FloatValue;
        static_assert(std::is_same_v<
            FloatColumnType::ValueType,
            std::optional<float>>);
        static_assert(std::is_same_v<
            FloatColumnType::ValueTraits,
            sqt::NullableValueTraits<std::optional<float>>>);
        static_assert(std::is_same_v<
            typename FloatColumnType::DefaultValueType,
            std::optional<float>>);
        static_assert((FloatColumnType::DefaultValue == std::optional<float>{ 3.14f }));
        constexpr const auto& float_column = table.FloatValue;
        constexpr sqt::DataType data_type = float_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Float);
        constexpr bool is_nullable = float_column.IsNullable();
        ASSERT_EQ(is_nullable, true);
        ASSERT_EQ(float_column.GetDefaultValueSQLLiteral(), "3.140000");
    }

    {
        using DoubleColumnType = TableType::ColumnType_DoubleValue;
        static_assert(std::is_same_v<
            DoubleColumnType::ValueType,
            std::optional<double>>);
        static_assert(std::is_same_v<
            DoubleColumnType::ValueTraits,
            sqt::NullableValueTraits<std::optional<double>>>);
        static_assert(std::is_same_v<
            typename DoubleColumnType::DefaultValueType,
            std::optional<double>>);
        static_assert((DoubleColumnType::DefaultValue == std::optional<double>{ 3.1415926 }));
        constexpr const auto& double_column = table.DoubleValue;
        constexpr sqt::DataType data_type = double_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Float);
        constexpr bool is_nullable = double_column.IsNullable();
        ASSERT_EQ(is_nullable, true);
        ASSERT_EQ(double_column.GetDefaultValueSQLLiteral(), "3.141593");
    }

    {
        using StringColumnType = TableType::ColumnType_StringValue;
        static_assert(std::is_same_v<
            StringColumnType::ValueType,
            std::optional<std::string>>);
        static_assert(std::is_same_v<
            StringColumnType::ValueTraits,
            sqt::NullableValueTraits<std::optional<std::string>>>);
        static_assert(std::is_same_v<
            typename StringColumnType::DefaultValueType,
            std::optional<std::string_view>>);
        static_assert((
            StringColumnType::DefaultValue == std::optional<std::string_view>{ "Hello" }));
        constexpr const auto& string_column = table.StringValue;
        constexpr sqt::DataType data_type = string_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Text);
        constexpr bool is_nullable = string_column.IsNullable();
        ASSERT_EQ(is_nullable, true);
        ASSERT_EQ(string_column.GetDefaultValueSQLLiteral(), "'Hello'");
    }
}


namespace column_def_test {
struct NullableValueEntity {
    std::optional<bool> bool_value;
    std::optional<char> char_value;
    std::optional<signed char> signed_char_value;
    std::optional<unsigned char> unsigned_char_value;
    std::optional<char8_t> char8_t_value;
    std::optional<char16_t> char16_t_value;
    std::optional<char32_t> char32_t_value;
    std::optional<wchar_t> wchar_t_value;
    std::optional<short> short_value;
    std::optional<unsigned short> unsigned_short_value;
    std::optional<int> int_value;
    std::optional<unsigned int> unsigned_int_value;
    std::optional<long> long_value;
    std::optional<unsigned long> unsigned_long_value;
    std::optional<long long> long_long_value;
    std::optional<unsigned long long> unsigned_long_long_value;
    std::optional<float> float_value;
    std::optional<double> double_value;
    std::optional<std::string> string_value;
};
SQT_TABLE_BEGIN(NullableValueEntity, NullableValueEntity)
SQT_COLUMN_FIELD(BoolValue, bool_value)
SQT_COLUMN_FIELD(CharValue, char_value)
SQT_COLUMN_FIELD(SignedCharValue, signed_char_value)
SQT_COLUMN_FIELD(UnsignedCharValue, unsigned_char_value)
SQT_COLUMN_FIELD(Char8TValue, char8_t_value)
SQT_COLUMN_FIELD(Char16TValue, char16_t_value)
SQT_COLUMN_FIELD(Char32TValue, char32_t_value)
SQT_COLUMN_FIELD(WCharTValue, wchar_t_value)
SQT_COLUMN_FIELD(ShortValue, short_value)
SQT_COLUMN_FIELD(UnsignedShortValue, unsigned_short_value)
SQT_COLUMN_FIELD(IntValue, int_value)
SQT_COLUMN_FIELD(UnsignedIntValue, unsigned_int_value)
SQT_COLUMN_FIELD(LongValue, long_value)
SQT_COLUMN_FIELD(UnsignedLongValue, unsigned_long_value)
SQT_COLUMN_FIELD(LongLongValue, long_long_value)
SQT_COLUMN_FIELD(UnsignedLongLongValue, unsigned_long_long_value)
SQT_COLUMN_FIELD(FloatValue, float_value)
SQT_COLUMN_FIELD(DoubleValue, double_value)
SQT_COLUMN_FIELD(StringValue, string_value)
SQT_TABLE_END
}

SQT_REGISTER(column_def_test::NullableValueEntity)

TEST(ColumnDefinitionTest, NullableValues) {

    using TableType = sqt::TableType<column_def_test::NullableValueEntity>;
    constexpr const auto& table = sqt::Table<column_def_test::NullableValueEntity>;

    {
        using BoolColumnType = TableType::ColumnType_BoolValue;
        static_assert(std::is_same_v<BoolColumnType::ValueType, std::optional<bool>>);
        static_assert(std::is_same_v<
            BoolColumnType::ValueTraits,
            sqt::NullableValueTraits<std::optional<bool>>>);
        constexpr const auto& bool_column = table.BoolValue;
        constexpr sqt::DataType data_type = bool_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = bool_column.IsNullable();
        ASSERT_EQ(is_nullable, true);
        ASSERT_EQ(bool_column.GetDefaultValueSQLLiteral(), std::nullopt);
    }

    {
        using CharColumnType = TableType::ColumnType_CharValue;
        static_assert(std::is_same_v<CharColumnType::ValueType, std::optional<char>>);
        static_assert(std::is_same_v<
            CharColumnType::ValueTraits,
            sqt::NullableValueTraits<std::optional<char>>>);
        constexpr const auto& char_column = table.CharValue;
        constexpr sqt::DataType data_type = char_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = char_column.IsNullable();
        ASSERT_EQ(is_nullable, true);
        ASSERT_EQ(char_column.GetDefaultValueSQLLiteral(), std::nullopt);
    }

    {
        using SignedCharColumnType = TableType::ColumnType_SignedCharValue;
        static_assert(std::is_same_v<SignedCharColumnType::ValueType, std::optional<signed char>>);
        static_assert(std::is_same_v<
            SignedCharColumnType::ValueTraits,
            sqt::NullableValueTraits<std::optional<signed char>>>);
        constexpr const auto& signed_char_column = table.SignedCharValue;
        constexpr sqt::DataType data_type = signed_char_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = signed_char_column.IsNullable();
        ASSERT_EQ(is_nullable, true);
        ASSERT_EQ(signed_char_column.GetDefaultValueSQLLiteral(), std::nullopt);
    }

    {
        using UnsignedCharColumnType = TableType::ColumnType_UnsignedCharValue;
        static_assert(std::is_same_v<
            UnsignedCharColumnType::ValueType,
            std::optional<unsigned char>>);
        static_assert(std::is_same_v<
            UnsignedCharColumnType::ValueTraits,
            sqt::NullableValueTraits<std::optional<unsigned char>>>);
        constexpr const auto& unsigned_char_column = table.UnsignedCharValue;
        constexpr sqt::DataType data_type = unsigned_char_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = unsigned_char_column.IsNullable();
        ASSERT_EQ(is_nullable, true);
        ASSERT_EQ(unsigned_char_column.GetDefaultValueSQLLiteral(), std::nullopt);
    }

    {
        using Char8TColumnType = TableType::ColumnType_Char8TValue;
        static_assert(std::is_same_v<Char8TColumnType::ValueType, std::optional<char8_t>>);
        static_assert(std::is_same_v<
            Char8TColumnType::ValueTraits,
            sqt::NullableValueTraits<std::optional<char8_t>>>);
        constexpr const auto& char8_t_column = table.Char8TValue;
        constexpr sqt::DataType data_type = char8_t_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = char8_t_column.IsNullable();
        ASSERT_EQ(is_nullable, true);
        ASSERT_EQ(char8_t_column.GetDefaultValueSQLLiteral(), std::nullopt);
    }

    {
        using Char16TColumnType = TableType::ColumnType_Char16TValue;
        static_assert(std::is_same_v<Char16TColumnType::ValueType, std::optional<char16_t>>);
        static_assert(std::is_same_v<
            Char16TColumnType::ValueTraits,
            sqt::NullableValueTraits<std::optional<char16_t>>>);
        constexpr const auto& char16_t_column = table.Char16TValue;
        constexpr sqt::DataType data_type = char16_t_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = char16_t_column.IsNullable();
        ASSERT_EQ(is_nullable, true);
        ASSERT_EQ(char16_t_column.GetDefaultValueSQLLiteral(), std::nullopt);
    }

    {
        using Char32TColumnType = TableType::ColumnType_Char32TValue;
        static_assert(std::is_same_v<Char32TColumnType::ValueType, std::optional<char32_t>>);
        static_assert(std::is_same_v<
            Char32TColumnType::ValueTraits,
            sqt::NullableValueTraits<std::optional<char32_t>>>);
        constexpr const auto& char32_t_column = table.Char32TValue;
        constexpr sqt::DataType data_type = char32_t_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = char32_t_column.IsNullable();
        ASSERT_EQ(is_nullable, true);
        ASSERT_EQ(char32_t_column.GetDefaultValueSQLLiteral(), std::nullopt);
    }

    {
        using WCharTColumnType = TableType::ColumnType_WCharTValue;
        static_assert(std::is_same_v<WCharTColumnType::ValueType, std::optional<wchar_t>>);
        static_assert(std::is_same_v<
            WCharTColumnType::ValueTraits,
            sqt::NullableValueTraits<std::optional<wchar_t>>>);
        constexpr const auto& wchar_t_column = table.WCharTValue;
        constexpr sqt::DataType data_type = wchar_t_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = wchar_t_column.IsNullable();
        ASSERT_EQ(is_nullable, true);
        ASSERT_EQ(wchar_t_column.GetDefaultValueSQLLiteral(), std::nullopt);
    }

    {
        using ShortColumnType = TableType::ColumnType_ShortValue;
        static_assert(std::is_same_v<ShortColumnType::ValueType, std::optional<short>>);
        static_assert(std::is_same_v<
            ShortColumnType::ValueTraits,
            sqt::NullableValueTraits<std::optional<short>>>);
        constexpr const auto& short_column = table.ShortValue;
        constexpr sqt::DataType data_type = short_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = short_column.IsNullable();
        ASSERT_EQ(is_nullable, true);
        ASSERT_EQ(short_column.GetDefaultValueSQLLiteral(), std::nullopt);
    }

    {
        using UnsignedShortColumnType = TableType::ColumnType_UnsignedShortValue;
        static_assert(std::is_same_v<
            UnsignedShortColumnType::ValueType, 
            std::optional<unsigned short>>);
        static_assert(std::is_same_v<
            UnsignedShortColumnType::ValueTraits,
            sqt::NullableValueTraits<std::optional<unsigned short>>>);
        constexpr const auto& unsigned_short_column = table.UnsignedShortValue;
        constexpr sqt::DataType data_type = unsigned_short_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = unsigned_short_column.IsNullable();
        ASSERT_EQ(is_nullable, true);
        ASSERT_EQ(unsigned_short_column.GetDefaultValueSQLLiteral(), std::nullopt);
    }

    {
        using IntColumnType = TableType::ColumnType_IntValue;
        static_assert(std::is_same_v<IntColumnType::ValueType, std::optional<int>>);
        static_assert(std::is_same_v <
            IntColumnType::ValueTraits,
            sqt::NullableValueTraits<std::optional<int>>>);
        constexpr const auto& int_column = table.IntValue;
        constexpr sqt::DataType data_type = int_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = int_column.IsNullable();
        ASSERT_EQ(is_nullable, true);
        ASSERT_EQ(int_column.GetDefaultValueSQLLiteral(), std::nullopt);
    }

    {
        using UnsignedIntColumnType = TableType::ColumnType_UnsignedIntValue;
        static_assert(std::is_same_v<
            UnsignedIntColumnType::ValueType,
            std::optional<unsigned int>>);
        static_assert(std::is_same_v<
            UnsignedIntColumnType::ValueTraits,
            sqt::NullableValueTraits<std::optional<unsigned int>>>);
        constexpr const auto& unsigned_int_column = table.UnsignedIntValue;
        constexpr sqt::DataType data_type = unsigned_int_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = unsigned_int_column.IsNullable();
        ASSERT_EQ(is_nullable, true);
        ASSERT_EQ(unsigned_int_column.GetDefaultValueSQLLiteral(), std::nullopt);
    }

    {
        using LongColumnType = TableType::ColumnType_LongValue;
        static_assert(std::is_same_v<LongColumnType::ValueType, std::optional<long>>);
        static_assert(std::is_same_v<
            LongColumnType::ValueTraits,
            sqt::NullableValueTraits<std::optional<long>>>);
        constexpr const auto& long_column = table.LongValue;
        constexpr sqt::DataType data_type = long_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = long_column.IsNullable();
        ASSERT_EQ(is_nullable, true);
        ASSERT_EQ(long_column.GetDefaultValueSQLLiteral(), std::nullopt);
    }

    {
        using UnsignedLongColumnType = TableType::ColumnType_UnsignedLongValue;
        static_assert(std::is_same_v<
            UnsignedLongColumnType::ValueType,
            std::optional<unsigned long>>);
        static_assert(std::is_same_v <
            UnsignedLongColumnType::ValueTraits,
            sqt::NullableValueTraits<std::optional<unsigned long>>>);
        constexpr const auto& unsigned_long_column = table.UnsignedLongValue;
        constexpr sqt::DataType data_type = unsigned_long_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = unsigned_long_column.IsNullable();
        ASSERT_EQ(is_nullable, true);
        ASSERT_EQ(unsigned_long_column.GetDefaultValueSQLLiteral(), std::nullopt);
    }

    {
        using LongLongColumnType = TableType::ColumnType_LongLongValue;
        static_assert(std::is_same_v<LongLongColumnType::ValueType, std::optional<long long>>);
        static_assert(std::is_same_v <
            LongLongColumnType::ValueTraits,
            sqt::NullableValueTraits<std::optional<long long>>>);
        constexpr const auto& long_long_column = table.LongLongValue;
        constexpr sqt::DataType data_type = long_long_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = long_long_column.IsNullable();
        ASSERT_EQ(is_nullable, true);
        ASSERT_EQ(long_long_column.GetDefaultValueSQLLiteral(), std::nullopt);
    }

    {
        using UnsignedLongLongColumnType = TableType::ColumnType_UnsignedLongLongValue;
        static_assert(std::is_same_v<
            UnsignedLongLongColumnType::ValueType,
            std::optional<unsigned long long>>);
        static_assert(std::is_same_v<
            UnsignedLongLongColumnType::ValueTraits,
            sqt::NullableValueTraits<std::optional<unsigned long long>>>);
        constexpr const auto& unsigned_long_long_column = table.UnsignedLongLongValue;
        constexpr sqt::DataType data_type = unsigned_long_long_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Integer);
        constexpr bool is_nullable = unsigned_long_long_column.IsNullable();
        ASSERT_EQ(is_nullable, true);
        ASSERT_EQ(unsigned_long_long_column.GetDefaultValueSQLLiteral(), std::nullopt);
    }

    {
        using FloatColumnType = TableType::ColumnType_FloatValue;
        static_assert(std::is_same_v<FloatColumnType::ValueType, std::optional<float>>);
        static_assert(std::is_same_v <
            FloatColumnType::ValueTraits,
            sqt::NullableValueTraits<std::optional<float>>>);
        constexpr const auto& float_column = table.FloatValue;
        constexpr sqt::DataType data_type = float_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Float);
        constexpr bool is_nullable = float_column.IsNullable();
        ASSERT_EQ(is_nullable, true);
        ASSERT_EQ(float_column.GetDefaultValueSQLLiteral(), std::nullopt);
    }

    {
        using DoubleColumnType = TableType::ColumnType_DoubleValue;
        static_assert(std::is_same_v<DoubleColumnType::ValueType, std::optional<double>>);
        static_assert(std::is_same_v <
            DoubleColumnType::ValueTraits,
            sqt::NullableValueTraits<std::optional<double>>>);
        constexpr const auto& double_column = table.DoubleValue;
        constexpr sqt::DataType data_type = double_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Float);
        constexpr bool is_nullable = double_column.IsNullable();
        ASSERT_EQ(is_nullable, true);
        ASSERT_EQ(double_column.GetDefaultValueSQLLiteral(), std::nullopt);
    }

    {
        using StringColumnType = TableType::ColumnType_StringValue;
        static_assert(std::is_same_v<StringColumnType::ValueType, std::optional<std::string>>);
        static_assert(std::is_same_v <
            StringColumnType::ValueTraits,
            sqt::NullableValueTraits<std::optional<std::string>>>);
        constexpr const auto& string_column = table.StringValue;
        constexpr sqt::DataType data_type = string_column.GetDataType();
        ASSERT_EQ(data_type, sqt::DataType::Text);
        constexpr bool is_nullable = string_column.IsNullable();
        ASSERT_EQ(is_nullable, true);
        ASSERT_EQ(string_column.GetDefaultValueSQLLiteral(), std::nullopt);
    }
}


/*
Test the SQT_COLUMN_FIELD_2 macro.
*/
namespace column_def_test {
struct FieldColumnsEntity {
    int value{};
};
SQT_TABLE_BEGIN(FieldColumnsEntity, FieldColumnsEntity)
SQT_COLUMN_FIELD_2(Value, CustomValue, value)
SQT_TABLE_END
}
SQT_REGISTER(column_def_test::FieldColumnsEntity)

TEST(ColumnDefinitionTest, FieldColumns) {

    using TableType = sqt::TableType<column_def_test::FieldColumnsEntity>;
    ASSERT_EQ(TableType::ColumnType_CustomValue::Name, "Value");

    constexpr auto& table = sqt::Table<column_def_test::FieldColumnsEntity>;
    ASSERT_EQ(table.CustomValue.GetName(), "Value");
}


/*
Test the SQT_COLUMN_ACCESSOR* macros.
*/
namespace column_def_test {
struct AccessorColumnsEntity {
    int GetValue() const {
        return 0;
    }
    void SetValue(int) {

    }
};
SQT_TABLE_BEGIN(AccessorColumnsEntity, AccessorColumnsEntity)
SQT_COLUMN_ACCESSOR(Value, GetValue, SetValue)
SQT_COLUMN_ACCESSOR_2(Value2, CustomValue, GetValue, SetValue)
SQT_TABLE_END
}
SQT_REGISTER(column_def_test::AccessorColumnsEntity)

TEST(ColumnDefinitionTest, AccessorColumns) {

    using TableType = sqt::TableType<column_def_test::AccessorColumnsEntity>;
    constexpr auto& table = sqt::Table<column_def_test::AccessorColumnsEntity>;

    ASSERT_EQ(TableType::ColumnType_Value::Name, "Value");
    ASSERT_EQ(TableType::ColumnType_CustomValue::Name, "Value2");
        
    ASSERT_EQ(table.Value.GetName(), "Value");
    ASSERT_EQ(table.CustomValue.GetName(), "Value2");
}


/*
Test the SQT_COLUMN_CUSTOM* macros.
*/
namespace column_def_test {
struct CustomColumnsEntity {
};
struct ValueSource {
    using ValueType = int;
    static int GetValueFromEntity(const CustomColumnsEntity&) {
        return 0;
    }
    static void SetValueToEntity(CustomColumnsEntity& entity, int value) {

    }
};
SQT_TABLE_BEGIN(CustomColumnsEntity, CustomColumnsEntity)
SQT_COLUMN_CUSTOM(Value, ValueSource)
SQT_COLUMN_CUSTOM_2(Value2, CustomValue, ValueSource)
SQT_TABLE_END
}
SQT_REGISTER(column_def_test::CustomColumnsEntity)

TEST(ColumnDefinitionTest, CustomColumns) {

    using TableType = sqt::TableType<column_def_test::CustomColumnsEntity>;
    constexpr auto& table = sqt::Table<column_def_test::CustomColumnsEntity>;

    ASSERT_EQ(TableType::ColumnType_Value::Name, "Value");
    ASSERT_EQ(TableType::ColumnType_CustomValue::Name, "Value2");

    ASSERT_EQ(table.Value.GetName(), "Value");
    ASSERT_EQ(table.CustomValue.GetName(), "Value2");
}