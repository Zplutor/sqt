#include "data_context_test_fixture.h"

class DeleterTest : public DataContextTestFixture {

};


TEST_F(DeleterTest, DeleteAll) {

    constexpr auto deleter = NoPKContext::MakeDeleter();

    auto executor = GetNoPKContext().Prepare(deleter);
    executor.Execute();
    ASSERT_EQ(executor.LastChanges(), 3);
    ASSERT_TRUE(CheckData(std::vector<test_entities::EntityNoPK>{}));
}


TEST_F(DeleterTest, Delete_Where) {

    constexpr auto deleter = NoPKContext::MakeDeleter().Where(NoPKTable.ID == 3);
    auto executor = GetNoPKContext().Prepare(deleter);
    executor.Execute();
    ASSERT_EQ(executor.LastChanges(), 1);
    ASSERT_TRUE(CheckData({
        test_entities::EntityNoPK{ 1, "1" },
        test_entities::EntityNoPK{ 2, "2" },
    }));
}