#include "data_context_test_fixture.h"

class DeleterTest : public DataContextTestFixture {

};


TEST_F(DeleterTest, DeleteAll) {

    constexpr auto deleter = NoPKContext::MakeDeleter();

    auto executor = GetNoPKContext().Prepare(deleter);
    executor.Execute();

    ASSERT_TRUE(CheckData({}));
}


TEST_F(DeleterTest, Delete_Where) {

    constexpr auto deleter = NoPKContext::MakeDeleter().Where(NoPKTable.ID == 3);
    GetNoPKContext().Prepare(deleter).Execute();

    ASSERT_TRUE(CheckData({
        data_context_test::EntityNoPK{ 1, "1" },
        data_context_test::EntityNoPK{ 2, "2" },
    }));
}