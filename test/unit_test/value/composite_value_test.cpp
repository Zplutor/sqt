#include <gtest/gtest.h>
#include <sqt/orm/value/trivial/basic/nullable_value_traits.h>
#include <sqt/orm/value/trivial/basic/primitive_value_traits.h>
#include <sqt/orm/value/trivial/composite/composite_value_traits.h>
#include <sqt/orm/value/trivial/composite/composite_value_traits_type.h>
#include <sqt/orm/value/trivial/composite/composite_value_type.h>
#include "unit_test/fixture/blob.h"

TEST(CompositeValueTest, CompositeValueType) {

    //Primitive types
    ASSERT_TRUE(sqt::CompositeValueType<std::tuple<bool>>);
    ASSERT_TRUE(sqt::CompositeValueType<std::tuple<char>>);
    ASSERT_TRUE(sqt::CompositeValueType<std::tuple<signed char>>);
    ASSERT_TRUE(sqt::CompositeValueType<std::tuple<unsigned char>>);
    ASSERT_TRUE(sqt::CompositeValueType<std::tuple<char8_t>>);
    ASSERT_TRUE(sqt::CompositeValueType<std::tuple<char16_t>>);
    ASSERT_TRUE(sqt::CompositeValueType<std::tuple<char32_t>>);
    ASSERT_TRUE(sqt::CompositeValueType<std::tuple<wchar_t>>);
    ASSERT_TRUE(sqt::CompositeValueType<std::tuple<short>>);
    ASSERT_TRUE(sqt::CompositeValueType<std::tuple<unsigned short>>);
    ASSERT_TRUE(sqt::CompositeValueType<std::tuple<int>>);
    ASSERT_TRUE(sqt::CompositeValueType<std::tuple<unsigned int>>);
    ASSERT_TRUE(sqt::CompositeValueType<std::tuple<long>>);
    ASSERT_TRUE(sqt::CompositeValueType<std::tuple<unsigned long>>);
    ASSERT_TRUE(sqt::CompositeValueType<std::tuple<long long>>);
    ASSERT_TRUE(sqt::CompositeValueType<std::tuple<unsigned long long>>);
    ASSERT_TRUE(sqt::CompositeValueType<std::tuple<float>>);
    ASSERT_TRUE(sqt::CompositeValueType<std::tuple<double>>);
    ASSERT_TRUE(sqt::CompositeValueType<std::tuple<long double>>);
    ASSERT_TRUE(sqt::CompositeValueType<std::tuple<std::string>>);

    //Nullable types
    ASSERT_TRUE(sqt::CompositeValueType<std::tuple<std::optional<bool>>>);
    ASSERT_TRUE(sqt::CompositeValueType<std::tuple<std::optional<char>>>);
    ASSERT_TRUE(sqt::CompositeValueType<std::tuple<std::optional<signed char>>>);
    ASSERT_TRUE(sqt::CompositeValueType<std::tuple<std::optional<unsigned char>>>);
    ASSERT_TRUE(sqt::CompositeValueType<std::tuple<std::optional<char8_t>>>);
    ASSERT_TRUE(sqt::CompositeValueType<std::tuple<std::optional<char16_t>>>);
    ASSERT_TRUE(sqt::CompositeValueType<std::tuple<std::optional<char32_t>>>);
    ASSERT_TRUE(sqt::CompositeValueType<std::tuple<std::optional<wchar_t>>>);
    ASSERT_TRUE(sqt::CompositeValueType<std::tuple<std::optional<short>>>);
    ASSERT_TRUE(sqt::CompositeValueType<std::tuple<std::optional<unsigned short>>>);
    ASSERT_TRUE(sqt::CompositeValueType<std::tuple<std::optional<int>>>);
    ASSERT_TRUE(sqt::CompositeValueType<std::tuple<std::optional<unsigned int>>>);
    ASSERT_TRUE(sqt::CompositeValueType<std::tuple<std::optional<long>>>);
    ASSERT_TRUE(sqt::CompositeValueType<std::tuple<std::optional<unsigned long>>>);
    ASSERT_TRUE(sqt::CompositeValueType<std::tuple<std::optional<long long>>>);
    ASSERT_TRUE(sqt::CompositeValueType<std::tuple<std::optional<unsigned long long>>>);
    ASSERT_TRUE(sqt::CompositeValueType<std::tuple<std::optional<float>>>);
    ASSERT_TRUE(sqt::CompositeValueType<std::tuple<std::optional<double>>>);
    ASSERT_TRUE(sqt::CompositeValueType<std::tuple<std::optional<long double>>>);
    ASSERT_TRUE(sqt::CompositeValueType<std::tuple<std::optional<std::string>>>);

    //Custom type
    ASSERT_TRUE(sqt::CompositeValueType<std::tuple<BLOB>>);

    //Composition
    ASSERT_TRUE((sqt::CompositeValueType<std::tuple<int, std::string>>));
    ASSERT_TRUE((sqt::CompositeValueType<std::tuple<int, std::optional<int>>>));
    ASSERT_TRUE((sqt::CompositeValueType<std::tuple<int, std::optional<int>, BLOB>>));

    //Non-composite types
    ASSERT_FALSE(sqt::CompositeValueType<std::vector<int>>);
    ASSERT_FALSE(sqt::CompositeValueType<std::tuple<std::vector<int>>>);
    ASSERT_FALSE((sqt::CompositeValueType<std::tuple<int, std::vector<int>>>));
}


TEST(CompositeValueTest, CompositeValueTriats) {

    //Primitive value traits
    {
        using ValueTraits = sqt::CompositeValueTraits<sqt::PrimitiveValueTraits<int>>;
        ASSERT_TRUE((std::is_same_v<typename ValueTraits::ValueType, std::tuple<int>>));
        ASSERT_TRUE((std::is_same_v<
            typename ValueTraits::ValueTraitsTypes, 
            std::tuple<sqt::PrimitiveValueTraits<int>>>));
        ASSERT_TRUE(sqt::CompositeValueTraitsType<ValueTraits>);
    }

    //Nullable value traits
    {
        using ValueTraits = 
            sqt::CompositeValueTraits<sqt::NullableValueTraits<std::optional<int>>>;
        ASSERT_TRUE((std::is_same_v<
            typename ValueTraits::ValueType, 
            std::tuple<std::optional<int>>>));
        ASSERT_TRUE((std::is_same_v<
            typename ValueTraits::ValueTraitsTypes,
            std::tuple<sqt::NullableValueTraits<std::optional<int>>>>));
        ASSERT_TRUE(sqt::CompositeValueTraitsType<ValueTraits>);
    }

    //Custom value traits
    {
        using ValueTraits = sqt::CompositeValueTraits<sqt::CustomValueTraits<BLOB>>;
        ASSERT_TRUE((std::is_same_v<typename ValueTraits::ValueType, std::tuple<BLOB>>));
        ASSERT_TRUE((std::is_same_v<
            typename ValueTraits::ValueTraitsTypes,
            std::tuple<sqt::CustomValueTraits<BLOB>>>));
        ASSERT_TRUE(sqt::CompositeValueTraitsType<ValueTraits>);
    }

    //Composite value traits
    {
        using ValueTraits = sqt::CompositeValueTraits<
            sqt::PrimitiveValueTraits<int>,
            sqt::NullableValueTraits<std::optional<std::string>>,
            sqt::CustomValueTraits<BLOB>
        >;
        ASSERT_TRUE((std::is_same_v<
            typename ValueTraits::ValueType,
            std::tuple<int, std::optional<std::string>, BLOB>>));
        ASSERT_TRUE((std::is_same_v<
            typename ValueTraits::ValueTraitsTypes,
            std::tuple<
                sqt::PrimitiveValueTraits<int>,
                sqt::NullableValueTraits<std::optional<std::string>>,
                sqt::CustomValueTraits<BLOB>
            >>));
        ASSERT_TRUE(sqt::CompositeValueTraitsType<ValueTraits>);
    }
}