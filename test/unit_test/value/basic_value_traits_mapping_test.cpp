#include <gtest/gtest.h>
#include <sqt/orm/value/trivial/basic/basic_value_traits_mapping.h>

TEST(BasicValueTraitsMappingTest, PrimitiveValue) {

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


TEST(BasicValueTraitsMappingTest, NullableValue) {

    ASSERT_TRUE((std::is_same_v<
        sqt::BasicValueTraitsForT<std::optional<bool>>,
        sqt::NullableValueTraits<std::optional<bool>>>));
    ASSERT_TRUE((std::is_same_v<
        sqt::BasicValueTraitsForT<std::optional<int>>,
        sqt::NullableValueTraits<std::optional<int>>>));
    ASSERT_TRUE((std::is_same_v<
        sqt::BasicValueTraitsForT<std::optional<float>>,
        sqt::NullableValueTraits<std::optional<float>>>));
    ASSERT_TRUE((std::is_same_v<
        sqt::BasicValueTraitsForT<std::optional<std::string>>,
        sqt::NullableValueTraits<std::optional<std::string>>>));
}