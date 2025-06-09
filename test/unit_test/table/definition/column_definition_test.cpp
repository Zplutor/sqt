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
    }
}
