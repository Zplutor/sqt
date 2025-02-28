#include "data_context_test_fixture.h"

class SelecterTest : public DataContextTestFixture {

};


template<typename RESULT>
bool CheckResult(
    const RESULT& result, 
    const std::vector<typename RESULT::ValueType>& expected) {

    auto result_iterator = result.begin();
    auto expected_iterator = expected.begin();

    while (result_iterator != result.end() && 
           expected_iterator != expected.end()) {

        if (*result_iterator != *expected_iterator) {
            return false;
        }

        result_iterator++;
        expected_iterator++;
    }

    if (result_iterator != result.end() || expected_iterator != expected.end()) {
        return false;
    }
    return true;
}


TEST_F(SelecterTest, SelectEntity) {

    constexpr auto selecter = NoPKContext::MakeSelecter();

    auto executor = GetNoPKContext().Prepare(selecter);
    auto result = executor.Execute();

    ASSERT_TRUE(CheckResult(result, {
        data_context_test::EntityNoPK{ 1, "1" },
        data_context_test::EntityNoPK{ 2, "2" },
        data_context_test::EntityNoPK{ 3, "3" },
    }));
}


TEST_F(SelecterTest, SelectEntity_Where) {

    constexpr auto selecter = NoPKContext::MakeSelecter().Where(NoPKTable.ID == 2);

    auto executor = GetNoPKContext().Prepare(selecter);
    auto result = executor.Execute();

    ASSERT_TRUE(CheckResult(result, {
        data_context_test::EntityNoPK{ 2, "2" },
    }));
}


TEST_F(SelecterTest, SelectEntity_Where_Limit) {

    constexpr auto selecter = NoPKContext::MakeSelecter().Where(NoPKTable.ID < 5).Limit(2);

    auto executor = GetNoPKContext().Prepare(selecter);
    auto result = executor.Execute();

    ASSERT_TRUE(CheckResult(result, {
        data_context_test::EntityNoPK{ 1, "1" },
        data_context_test::EntityNoPK{ 2, "2" },
    }));
}


TEST_F(SelecterTest, SelectEntity_Limit) {

    constexpr auto selecter = NoPKContext::MakeSelecter().Limit(1);

    auto executor = GetNoPKContext().Prepare(selecter);
    auto result = executor.Execute();

    ASSERT_TRUE(CheckResult(result, {
        data_context_test::EntityNoPK{ 1, "1" },
    }));
}


TEST_F(SelecterTest, SelectOneColumn) {

    //All
    {
        constexpr auto selecter = NoPKContext::MakeSelecter(NoPKTable.ID);
        auto executor = GetNoPKContext().Prepare(selecter);
        auto result = executor.Execute();
        ASSERT_TRUE(CheckResult(result, { 1, 2, 3 }));
    }

    //Where
    {
        constexpr auto selecter = NoPKContext::MakeSelecter(NoPKTable.ID).Where(NoPKTable.ID == 3);
        auto executor = GetNoPKContext().Prepare(selecter);
        auto result = executor.Execute();
        ASSERT_TRUE(CheckResult(result, { 3 }));
    }

    //Where + Limit
    {
        constexpr auto selecter = 
            NoPKContext::MakeSelecter(NoPKTable.ID).Where(NoPKTable.ID < 3).Limit(1);
        auto executor = GetNoPKContext().Prepare(selecter);
        auto result = executor.Execute();
        ASSERT_TRUE(CheckResult(result, { 1 }));
    }

    //Limit
    {
        constexpr auto selecter = NoPKContext::MakeSelecter(NoPKTable.ID).Limit(2);
        auto executor = GetNoPKContext().Prepare(selecter);
        auto result = executor.Execute();
        ASSERT_TRUE(CheckResult(result, { 1, 2 }));
    }
}


TEST_F(SelecterTest, SelectTwoColumn) {

    constexpr auto selecter = NoPKContext::MakeSelecter(NoPKTable.ID, NoPKTable.Name);

    auto executor = GetNoPKContext().Prepare(selecter);
    auto result = executor.Execute();

    ASSERT_TRUE(CheckResult(result, { 
        std::tuple{ 1, "1" },
        std::tuple{ 2, "2" },
        std::tuple{ 3, "3" },
    }));
}