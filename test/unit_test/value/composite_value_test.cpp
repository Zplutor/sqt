#include <gtest/gtest.h>
#include <sqt/orm/value/trivial/basic/nullable_value_traits.h>
#include <sqt/orm/value/trivial/basic/primitive_value_traits.h>
#include <sqt/orm/value/trivial/composite/composite_value_traits.h>
#include <sqt/orm/value/trivial/composite/composite_value_traits_type.h>
#include <sqt/orm/value/trivial/composite/composite_value_type.h>
#include "unit_test/fixture/blob.h"

TEST(CompositeValueTest, CompositeValueType) {

    //Primitive types
    static_assert(sqt::CompositeValueType<std::tuple<bool>>);
    static_assert(sqt::CompositeValueType<std::tuple<char>>);
    static_assert(sqt::CompositeValueType<std::tuple<signed char>>);
    static_assert(sqt::CompositeValueType<std::tuple<unsigned char>>);
    static_assert(sqt::CompositeValueType<std::tuple<char8_t>>);
    static_assert(sqt::CompositeValueType<std::tuple<char16_t>>);
    static_assert(sqt::CompositeValueType<std::tuple<char32_t>>);
    static_assert(sqt::CompositeValueType<std::tuple<wchar_t>>);
    static_assert(sqt::CompositeValueType<std::tuple<short>>);
    static_assert(sqt::CompositeValueType<std::tuple<unsigned short>>);
    static_assert(sqt::CompositeValueType<std::tuple<int>>);
    static_assert(sqt::CompositeValueType<std::tuple<unsigned int>>);
    static_assert(sqt::CompositeValueType<std::tuple<long>>);
    static_assert(sqt::CompositeValueType<std::tuple<unsigned long>>);
    static_assert(sqt::CompositeValueType<std::tuple<long long>>);
    static_assert(sqt::CompositeValueType<std::tuple<unsigned long long>>);
    static_assert(sqt::CompositeValueType<std::tuple<float>>);
    static_assert(sqt::CompositeValueType<std::tuple<double>>);
    static_assert(sqt::CompositeValueType<std::tuple<std::string>>);

    //Nullable types
    static_assert(sqt::CompositeValueType<std::tuple<std::optional<bool>>>);
    static_assert(sqt::CompositeValueType<std::tuple<std::optional<char>>>);
    static_assert(sqt::CompositeValueType<std::tuple<std::optional<signed char>>>);
    static_assert(sqt::CompositeValueType<std::tuple<std::optional<unsigned char>>>);
    static_assert(sqt::CompositeValueType<std::tuple<std::optional<char8_t>>>);
    static_assert(sqt::CompositeValueType<std::tuple<std::optional<char16_t>>>);
    static_assert(sqt::CompositeValueType<std::tuple<std::optional<char32_t>>>);
    static_assert(sqt::CompositeValueType<std::tuple<std::optional<wchar_t>>>);
    static_assert(sqt::CompositeValueType<std::tuple<std::optional<short>>>);
    static_assert(sqt::CompositeValueType<std::tuple<std::optional<unsigned short>>>);
    static_assert(sqt::CompositeValueType<std::tuple<std::optional<int>>>);
    static_assert(sqt::CompositeValueType<std::tuple<std::optional<unsigned int>>>);
    static_assert(sqt::CompositeValueType<std::tuple<std::optional<long>>>);
    static_assert(sqt::CompositeValueType<std::tuple<std::optional<unsigned long>>>);
    static_assert(sqt::CompositeValueType<std::tuple<std::optional<long long>>>);
    static_assert(sqt::CompositeValueType<std::tuple<std::optional<unsigned long long>>>);
    static_assert(sqt::CompositeValueType<std::tuple<std::optional<float>>>);
    static_assert(sqt::CompositeValueType<std::tuple<std::optional<double>>>);
    static_assert(sqt::CompositeValueType<std::tuple<std::optional<std::string>>>);

    //Custom type
    static_assert(sqt::CompositeValueType<std::tuple<BLOB>>);

    //Composition
    static_assert((sqt::CompositeValueType<std::tuple<int, std::string>>));
    static_assert((sqt::CompositeValueType<std::tuple<int, std::optional<int>>>));
    static_assert((sqt::CompositeValueType<std::tuple<int, std::optional<int>, BLOB>>));

    //Non-composite types
    static_assert(!sqt::CompositeValueType<std::vector<int>>);
    static_assert(!sqt::CompositeValueType<std::tuple<std::vector<int>>>);
    static_assert(!(sqt::CompositeValueType<std::tuple<int, std::vector<int>>>));
    static_assert(!sqt::CompositeValueType<std::tuple<long double>>);
    static_assert(!sqt::CompositeValueType<std::tuple<std::optional<long double>>>);
}


TEST(CompositeValueTest, CompositeValueTriats) {

    //Primitive value traits
    {
        using ValueTraits = sqt::CompositeValueTraits<sqt::PrimitiveValueTraits<int>>;
        static_assert((std::is_same_v<typename ValueTraits::ValueType, std::tuple<int>>));
        static_assert((std::is_same_v<
            typename ValueTraits::ValueTraitsTypes, 
            std::tuple<sqt::PrimitiveValueTraits<int>>>));
        static_assert(sqt::CompositeValueTraitsType<ValueTraits>);
    }

    //Nullable value traits
    {
        using ValueTraits = 
            sqt::CompositeValueTraits<sqt::NullableValueTraits<std::optional<int>>>;
        static_assert((std::is_same_v<
            typename ValueTraits::ValueType, 
            std::tuple<std::optional<int>>>));
        static_assert((std::is_same_v<
            typename ValueTraits::ValueTraitsTypes,
            std::tuple<sqt::NullableValueTraits<std::optional<int>>>>));
        static_assert(sqt::CompositeValueTraitsType<ValueTraits>);
    }

    //Custom value traits
    {
        using ValueTraits = sqt::CompositeValueTraits<sqt::CustomValueTraits<BLOB>>;
        static_assert((std::is_same_v<typename ValueTraits::ValueType, std::tuple<BLOB>>));
        static_assert((std::is_same_v<
            typename ValueTraits::ValueTraitsTypes,
            std::tuple<sqt::CustomValueTraits<BLOB>>>));
        static_assert(sqt::CompositeValueTraitsType<ValueTraits>);
    }

    //Composite value traits
    {
        using ValueTraits = sqt::CompositeValueTraits<
            sqt::PrimitiveValueTraits<int>,
            sqt::NullableValueTraits<std::optional<std::string>>,
            sqt::CustomValueTraits<BLOB>
        >;
        static_assert((std::is_same_v<
            typename ValueTraits::ValueType,
            std::tuple<int, std::optional<std::string>, BLOB>>));
        static_assert((std::is_same_v<
            typename ValueTraits::ValueTraitsTypes,
            std::tuple<
                sqt::PrimitiveValueTraits<int>,
                sqt::NullableValueTraits<std::optional<std::string>>,
                sqt::CustomValueTraits<BLOB>
            >>));
        static_assert(sqt::CompositeValueTraitsType<ValueTraits>);
    }
}