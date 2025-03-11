#include "unit_test/data_context_test_fixture.h"

class DataContextSelectTest : public DataContextTestFixture {

};


TEST_F(DataContextSelectTest, SelectAll) {

    {
        auto result = GetNoPKContext().SelectAll();
        ASSERT_TRUE(CheckData(result));
    }

    {
        auto result = GetPK1Context().SelectAll();
        ASSERT_TRUE(CheckData(result));
    }

    {
        auto result = GetPK2Context().SelectAll();
        ASSERT_TRUE(CheckData(result));
    }
}


TEST_F(DataContextSelectTest, Select) {

    //Single column primary key
    {
        auto result = GetPK1Context().Select(4);
        ASSERT_FALSE(result.has_value());

        result = GetPK1Context().Select(2);
        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(*result, (test_entities::EntityPK1{ 2, "2" }));
    }

    //Multiple column primary key
    {
        auto result = GetPK2Context().Select(std::make_tuple(5, "5"));
        ASSERT_FALSE(result.has_value());

        result = GetPK2Context().Select(std::make_tuple(3, "3"));
        ASSERT_TRUE(result.has_value());
        ASSERT_EQ(*result, (test_entities::EntityPK2{ 3, "3", 30 }));
    }
}