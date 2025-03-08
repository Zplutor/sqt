#include "data_context_test_fixture.h"

class DeleterTest : public DataContextTestFixture {

};


TEST_F(DeleterTest, DeleteAll) {

    constexpr auto deleter = NoPKContext::MakeDeleter();

    auto executor = GetNoPKContext().Prepare(deleter);
    auto changes = executor.Execute();
    ASSERT_EQ(changes, 3);
    ASSERT_TRUE(CheckData(std::vector<test_entities::EntityNoPK>{}));
}


TEST_F(DeleterTest, Delete_Where) {

    constexpr auto deleter = NoPKContext::MakeDeleter().Where(NoPKTable.ID == 3);
    auto changes = GetNoPKContext().Prepare(deleter).Execute();
    ASSERT_EQ(changes, 1);

    ASSERT_TRUE(CheckData({
        test_entities::EntityNoPK{ 1, "1" },
        test_entities::EntityNoPK{ 2, "2" },
    }));
}


TEST_F(DeleterTest, DataContext_Delete) {

    //Single column primary key
    {
        bool deleted = GetPK1Context().Delete(4);
        ASSERT_FALSE(deleted);

        deleted = GetPK1Context().Delete(3);
        ASSERT_TRUE(deleted);
        ASSERT_TRUE(CheckData({
            test_entities::EntityPK1{ 1, "1" },
            test_entities::EntityPK1{ 2, "2" },
        }));
    }

    //Multiple columns primary key
    {
        bool deleted = GetPK2Context().Delete({ 4, "4" });
        ASSERT_FALSE(deleted);

        deleted = GetPK2Context().Delete({ 3, "3" });
        ASSERT_TRUE(deleted);
        ASSERT_TRUE(CheckData({
            test_entities::EntityPK2{ 1, "1", 10 },
            test_entities::EntityPK2{ 2, "2", 20 },
        }));
    }
}