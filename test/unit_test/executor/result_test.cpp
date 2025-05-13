#include <gtest/gtest.h>
#include <sqt/orm/data_context.h>
#include <sqt/orm/table_mapping.h>
#include "unit_test/fixture/test_entities.h"
#include "unit_test/data_context_test_fixture.h"

class ResultTest : public DataContextTestFixture {

};


TEST_F(ResultTest, ToVector) {

    constexpr auto selecter = NoPKContext::MakeSelecter();
    auto executor = GetNoPKContext().Prepare(selecter);
    auto result = executor.Execute();
    auto vector = result.ToVector();

    std::vector<test_entities::EntityNoPK> expected{
        test_entities::EntityNoPK{ 1, "1" },
        test_entities::EntityNoPK{ 2, "2" },
        test_entities::EntityNoPK{ 3, "3" },
    };
    ASSERT_EQ(vector, expected);
}


TEST_F(ResultTest, ToList) {

    constexpr auto selecter = NoPKContext::MakeSelecter();
    auto executor = GetNoPKContext().Prepare(selecter);
    auto result = executor.Execute();
    auto list = result.ToList();

    std::list<test_entities::EntityNoPK> expected{
        test_entities::EntityNoPK{ 1, "1" },
        test_entities::EntityNoPK{ 2, "2" },
        test_entities::EntityNoPK{ 3, "3" },
    };
    ASSERT_EQ(list, expected);
}


TEST_F(ResultTest, ToDeque) {

    constexpr auto selecter = NoPKContext::MakeSelecter();
    auto executor = GetNoPKContext().Prepare(selecter);
    auto result = executor.Execute();
    auto deque = result.ToDeque();

    std::deque<test_entities::EntityNoPK> expected{
        test_entities::EntityNoPK{ 1, "1" },
        test_entities::EntityNoPK{ 2, "2" },
        test_entities::EntityNoPK{ 3, "3" },
    };
    ASSERT_EQ(deque, expected);
}