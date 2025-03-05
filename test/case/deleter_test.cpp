#include "data_context_test_fixture.h"

class DeleterTest : public DataContextTestFixture {

};


TEST_F(DeleterTest, DeleteAll) {

    constexpr auto deleter = NoPKContext::MakeDeleter();

    auto executor = GetNoPKContext().Prepare(deleter);
    auto changes = executor.Execute();
    ASSERT_EQ(changes, 3);
    ASSERT_TRUE(CheckData(std::vector<data_context_test::EntityNoPK>{}));
}


TEST_F(DeleterTest, Delete_Where) {

    constexpr auto deleter = NoPKContext::MakeDeleter().Where(NoPKTable.ID == 3);
    auto changes = GetNoPKContext().Prepare(deleter).Execute();
    ASSERT_EQ(changes, 1);

    ASSERT_TRUE(CheckData({
        data_context_test::EntityNoPK{ 1, "1" },
        data_context_test::EntityNoPK{ 2, "2" },
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
            data_context_test::EntityPK1{ 1, "1" },
            data_context_test::EntityPK1{ 2, "2" },
        }));
    }

    //Multiple columns primary key
    {
        bool deleted = GetPK2Context().Delete({ 4, "4" });
        ASSERT_FALSE(deleted);

        deleted = GetPK2Context().Delete({ 3, "3" });
        ASSERT_TRUE(deleted);
        ASSERT_TRUE(CheckData({
            data_context_test::EntityPK2{ 1, "1", 10 },
            data_context_test::EntityPK2{ 2, "2", 20 },
        }));
    }
}