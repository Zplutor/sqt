#include "unit_test/data_context_test_fixture.h"

class DataContextDeleteTest : public DataContextTestFixture {

};


TEST_F(DataContextDeleteTest, DeleteAll) {

    auto& context = GetNoPKContext();
    ASSERT_EQ(context.DeleteAll(), 3);
    ASSERT_TRUE(CheckData(std::vector<test_entities::EntityNoPK>{}));
}


TEST_F(DataContextDeleteTest, Delete) {

    //Single column pk
    {
        auto& context = GetPK1Context();
        ASSERT_TRUE(context.Delete(1));
        ASSERT_FALSE(context.Delete(1));
        ASSERT_FALSE(context.Delete(4));
        ASSERT_TRUE(CheckData({
            test_entities::EntityPK1{ 2, "2" },
            test_entities::EntityPK1{ 3, "3" },
        }));
    }

    //Multiple columns pk
    {
        auto& context = GetPK2Context();
        ASSERT_TRUE(context.Delete(std::make_tuple(1, "1")));
        ASSERT_FALSE(context.Delete(std::make_tuple(1, "1")));
        ASSERT_FALSE(context.Delete(std::make_tuple(4, "4")));
        ASSERT_TRUE(CheckData({
            test_entities::EntityPK2{ 2, "2", 20 },
            test_entities::EntityPK2{ 3, "3", 30 },
        }));
    }
}