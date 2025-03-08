#include "unit_test/data_context_test_fixture.h"

class DataContextUpdateTest : public DataContextTestFixture {

};


TEST_F(DataContextUpdateTest, Update) {

    //Single column primary key
    {
        test_entities::EntityPK1 entity{ 4, "updated" };
        auto updated = GetPK1Context().Update(entity);
        ASSERT_FALSE(updated);

        entity.id = 1;
        updated = GetPK1Context().Update(entity);
        ASSERT_TRUE(updated);
        ASSERT_TRUE(CheckData({
            test_entities::EntityPK1{ 1, "updated" },
            test_entities::EntityPK1{ 2, "2" },
            test_entities::EntityPK1{ 3, "3" },
        }));
    }

    //Multiple columns primary key
    {
        test_entities::EntityPK2 entity{ 1, "2", 40 };

        auto updated = GetPK2Context().Update(entity);
        ASSERT_FALSE(updated);

        entity.id = 1;
        entity.name = "1";
        entity.age = 40;
        updated = GetPK2Context().Update(entity);
        ASSERT_TRUE(updated);
        ASSERT_TRUE(CheckData({
            test_entities::EntityPK2{ 1, "1", 40 },
            test_entities::EntityPK2{ 2, "2", 20 },
            test_entities::EntityPK2{ 3, "3", 30 },
        }));
    }
}