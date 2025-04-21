#include "unit_test/data_context_test_fixture.h"

class SelecterTest : public DataContextTestFixture {

};


template<typename RESULT>
bool CheckResult(
    const RESULT& result, 
    const std::vector<typename RESULT::value_type>& expected) {

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

    //All
    {
        constexpr auto selecter = NoPKContext::MakeSelecter();
        auto executor = GetNoPKContext().Prepare(selecter);
        auto result = executor.Execute();
        ASSERT_TRUE(CheckResult(result, {
            test_entities::EntityNoPK{ 1, "1" },
            test_entities::EntityNoPK{ 2, "2" },
            test_entities::EntityNoPK{ 3, "3" },
        }));
    }

    //Where + OrderBy + Limit
    {
        constexpr auto selecter = NoPKContext::MakeSelecter()
            .Where(NoPKTable.ID == 1 || NoPKTable.ID == 3)
            .OrderBy(NoPKTable.ID.Desc())
            .Limit(1);
        auto executor = GetNoPKContext().Prepare(selecter);
        auto result = executor.Execute();
        ASSERT_TRUE(CheckResult(result, {
            test_entities::EntityNoPK{ 3, "3" },
        }));
    }

    //Where + OrderBy
    {
        constexpr auto selecter = NoPKContext::MakeSelecter()
            .Where(NoPKTable.ID == 1 || NoPKTable.ID == 3)
            .OrderBy(NoPKTable.ID.Desc());
        auto executor = GetNoPKContext().Prepare(selecter);
        auto result = executor.Execute();
        ASSERT_TRUE(CheckResult(result, {
            test_entities::EntityNoPK{ 3, "3" },
            test_entities::EntityNoPK{ 1, "1" },
        }));
    }

    //Where + Limit
    {
        constexpr auto selecter = NoPKContext::MakeSelecter().Where(NoPKTable.ID < 5).Limit(2);
        auto executor = GetNoPKContext().Prepare(selecter);
        auto result = executor.Execute();
        ASSERT_TRUE(CheckResult(result, {
            test_entities::EntityNoPK{ 1, "1" },
            test_entities::EntityNoPK{ 2, "2" },
        }));
    }

    //Where
    {
        constexpr auto selecter = NoPKContext::MakeSelecter().Where(NoPKTable.ID == 2);
        auto executor = GetNoPKContext().Prepare(selecter);
        auto result = executor.Execute();
        ASSERT_TRUE(CheckResult(result, {
            test_entities::EntityNoPK{ 2, "2" },
        }));
    }

    //OrderBy + Limit
    {
        constexpr auto selecter = NoPKContext::MakeSelecter()
            .OrderBy(NoPKTable.ID.Desc())
            .Limit(2);
        auto executor = GetNoPKContext().Prepare(selecter);
        auto result = executor.Execute();
        ASSERT_TRUE(CheckResult(result, {
            test_entities::EntityNoPK{ 3, "3" },
            test_entities::EntityNoPK{ 2, "2" },
        }));
    }

    //OrderBy
    {
        constexpr auto selecter = NoPKContext::MakeSelecter().OrderBy(NoPKTable.ID.Desc());
        auto executor = GetNoPKContext().Prepare(selecter);
        auto result = executor.Execute();
        ASSERT_TRUE(CheckResult(result, {
            test_entities::EntityNoPK{ 3, "3" },
            test_entities::EntityNoPK{ 2, "2" },
            test_entities::EntityNoPK{ 1, "1" },
        }));
    }

    //Limit
    {
        constexpr auto selecter = NoPKContext::MakeSelecter().Limit(1);
        auto executor = GetNoPKContext().Prepare(selecter);
        auto result = executor.Execute();
        ASSERT_TRUE(CheckResult(result, {
            test_entities::EntityNoPK{ 1, "1" },
        }));
    }
}


TEST_F(SelecterTest, SelectOneColumn) {

    //All
    {
        constexpr auto selecter = NoPKContext::MakeSelecter(NoPKTable.ID);
        auto executor = GetNoPKContext().Prepare(selecter);
        auto result = executor.Execute();
        ASSERT_TRUE(CheckResult(result, { 1, 2, 3 }));
    }

    //Where + OrderBy + Limit
    {
        constexpr auto selecter = NoPKContext::MakeSelecter(NoPKTable.ID)
            .Where(NoPKTable.ID == 1 || NoPKTable.ID == 3)
            .OrderBy(NoPKTable.ID.Desc())
            .Limit(1);
        auto executor = GetNoPKContext().Prepare(selecter);
        auto result = executor.Execute();
        ASSERT_TRUE(CheckResult(result, { 3 }));
    }

    //Where + OrderBy
    {
        constexpr auto selecter = NoPKContext::MakeSelecter(NoPKTable.ID)
            .Where(NoPKTable.ID == 1 || NoPKTable.ID == 3)
            .OrderBy(NoPKTable.ID.Desc());
        auto executor = GetNoPKContext().Prepare(selecter);
        auto result = executor.Execute();
        ASSERT_TRUE(CheckResult(result, { 3, 1 }));
    }

    //Where + Limit
    {
        constexpr auto selecter =
            NoPKContext::MakeSelecter(NoPKTable.ID).Where(NoPKTable.ID < 3).Limit(1);
        auto executor = GetNoPKContext().Prepare(selecter);
        auto result = executor.Execute();
        ASSERT_TRUE(CheckResult(result, { 1 }));
    }

    //Where
    {
        constexpr auto selecter = NoPKContext::MakeSelecter(NoPKTable.ID).Where(NoPKTable.ID == 3);
        auto executor = GetNoPKContext().Prepare(selecter);
        auto result = executor.Execute();
        ASSERT_TRUE(CheckResult(result, { 3 }));
    }

    //OrderBy + Limit
    {
        constexpr auto selecter = NoPKContext::MakeSelecter(NoPKTable.ID)
            .OrderBy(NoPKTable.ID.Desc())
            .Limit(2);
        auto executor = GetNoPKContext().Prepare(selecter);
        auto result = executor.Execute();
        ASSERT_TRUE(CheckResult(result, { 3, 2 }));
    }

    //OrderBy
    {
        constexpr auto selecter = NoPKContext::MakeSelecter(NoPKTable.ID)
            .OrderBy(NoPKTable.ID.Desc());
        auto executor = GetNoPKContext().Prepare(selecter);
        auto result = executor.Execute();
        ASSERT_TRUE(CheckResult(result, { 3, 2, 1 }));
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

    //All
    {
        constexpr auto selecter = NoPKContext::MakeSelecter(NoPKTable.ID, NoPKTable.Name);
        auto executor = GetNoPKContext().Prepare(selecter);
        auto result = executor.Execute();
        ASSERT_TRUE(CheckResult(result, {
            std::tuple{ 1, "1" },
            std::tuple{ 2, "2" },
            std::tuple{ 3, "3" },
        }));
    }

    //Where + OrderBy + Limit
    {
        constexpr auto selecter = NoPKContext::MakeSelecter(NoPKTable.ID, NoPKTable.Name)
            .Where(NoPKTable.ID == 1 || NoPKTable.ID == 3)
            .OrderBy(NoPKTable.ID.Desc())
            .Limit(1);
        auto executor = GetNoPKContext().Prepare(selecter);
        auto result = executor.Execute();
        ASSERT_TRUE(CheckResult(result, {
            std::tuple{ 3, "3" },
        }));
    }

    //Where + OrderBy
    {
        constexpr auto selecter = NoPKContext::MakeSelecter(NoPKTable.ID, NoPKTable.Name)
            .Where(NoPKTable.ID == 1 || NoPKTable.ID == 3)
            .OrderBy(NoPKTable.ID.Desc());
        auto executor = GetNoPKContext().Prepare(selecter);
        auto result = executor.Execute();
        ASSERT_TRUE(CheckResult(result, {
            std::tuple{ 3, "3" },
            std::tuple{ 1, "1" },
        }));
    }

    //Where + Limit
    {
        constexpr auto selecter =
            NoPKContext::MakeSelecter(NoPKTable.ID, NoPKTable.Name)
            .Where(NoPKTable.ID < 5)
            .Limit(2);
        auto executor = GetNoPKContext().Prepare(selecter);
        auto result = executor.Execute();
        ASSERT_TRUE(CheckResult(result, {
            std::tuple{ 1, "1" },
            std::tuple{ 2, "2" },
        }));
    }

    //Where
    {
        constexpr auto selecter = 
            NoPKContext::MakeSelecter(NoPKTable.ID, NoPKTable.Name).Where(NoPKTable.ID == 2);
        auto executor = GetNoPKContext().Prepare(selecter);
        auto result = executor.Execute();
        ASSERT_TRUE(CheckResult(result, {
            std::tuple{ 2, "2" },
        }));
    }

    //OrderBy + Limit
    {
        constexpr auto selecter = NoPKContext::MakeSelecter(NoPKTable.ID, NoPKTable.Name)
            .OrderBy(NoPKTable.ID.Desc())
            .Limit(2);
        auto executor = GetNoPKContext().Prepare(selecter);
        auto result = executor.Execute();
        ASSERT_TRUE(CheckResult(result, {
            std::tuple{ 3, "3" },
            std::tuple{ 2, "2" },
        }));
    }

    //OrderBy
    {
        constexpr auto selecter = NoPKContext::MakeSelecter(NoPKTable.ID, NoPKTable.Name)
            .OrderBy(NoPKTable.ID.Desc());
        auto executor = GetNoPKContext().Prepare(selecter);
        auto result = executor.Execute();
        ASSERT_TRUE(CheckResult(result, {
            std::tuple{ 3, "3" },
            std::tuple{ 2, "2" },
            std::tuple{ 1, "1" },
        }));
    }

    //Limit
    {
        constexpr auto selecter = NoPKContext::MakeSelecter(NoPKTable.ID, NoPKTable.Name).Limit(2);
        auto executor = GetNoPKContext().Prepare(selecter);
        auto result = executor.Execute();
        ASSERT_TRUE(CheckResult(result, {
            std::tuple{ 1, "1" },
            std::tuple{ 2, "2" },
        }));
    }
}


TEST_F(SelecterTest, WhereSelecter_Column) {

    //Equal
    {
        constexpr auto selecter = NoPKContext::MakeSelecter().Where(NoPKTable.ID == 2);
        auto executor = GetNoPKContext().Prepare(selecter);
        auto result = executor.Execute();
        ASSERT_TRUE(CheckResult(result, {
            test_entities::EntityNoPK{ 2, "2" },
        }));
    }

    //Not equal
    {
        constexpr auto selecter = NoPKContext::MakeSelecter().Where(NoPKTable.ID != 2);
        auto executor = GetNoPKContext().Prepare(selecter);
        auto result = executor.Execute();
        ASSERT_TRUE(CheckResult(result, {
            test_entities::EntityNoPK{ 1, "1" },
            test_entities::EntityNoPK{ 3, "3" },
        }));
    }

    //Less
    {
        constexpr auto selecter = NoPKContext::MakeSelecter().Where(NoPKTable.ID < 2);
        auto executor = GetNoPKContext().Prepare(selecter);
        auto result = executor.Execute();
        ASSERT_TRUE(CheckResult(result, {
            test_entities::EntityNoPK{ 1, "1" },
        }));
    }

    //Less equal
    {
        constexpr auto selecter = NoPKContext::MakeSelecter().Where(NoPKTable.ID <= 2);
        auto executor = GetNoPKContext().Prepare(selecter);
        auto result = executor.Execute();
        ASSERT_TRUE(CheckResult(result, {
            test_entities::EntityNoPK{ 1, "1" },
            test_entities::EntityNoPK{ 2, "2" },
        }));
    }

    //Greater
    {
        constexpr auto selecter = NoPKContext::MakeSelecter().Where(NoPKTable.ID > 2);
        auto executor = GetNoPKContext().Prepare(selecter);
        auto result = executor.Execute();
        ASSERT_TRUE(CheckResult(result, {
            test_entities::EntityNoPK{ 3, "3" },
        }));
    }

    //Greater equal
    {
        constexpr auto selecter = NoPKContext::MakeSelecter().Where(NoPKTable.ID >= 2);
        auto executor = GetNoPKContext().Prepare(selecter);
        auto result = executor.Execute();
        ASSERT_TRUE(CheckResult(result, {
            test_entities::EntityNoPK{ 2, "2" },
            test_entities::EntityNoPK{ 3, "3" },
        }));
    }

    //And
    {
        constexpr auto selecter = NoPKContext::MakeSelecter()
            .Where(NoPKTable.ID > 1 && NoPKTable.ID < 3);
        auto executor = GetNoPKContext().Prepare(selecter);
        auto result = executor.Execute();
        ASSERT_TRUE(CheckResult(result, {
            test_entities::EntityNoPK{ 2, "2" },
        }));
    }

    //Or
    {
        constexpr auto selecter = NoPKContext::MakeSelecter()
            .Where(NoPKTable.ID < 2 || NoPKTable.ID > 2);
        auto executor = GetNoPKContext().Prepare(selecter);
        auto result = executor.Execute();
        ASSERT_TRUE(CheckResult(result, {
            test_entities::EntityNoPK{ 1, "1" },
            test_entities::EntityNoPK{ 3, "3" },
        }));
    }
}


TEST_F(SelecterTest, WhereSelecter_PrimaryKey) {

    //Use with single column primary key
    {
        constexpr auto selecter = PK1Context::MakeSelecter().Where(PK1Table.PrimaryKey == 1);
        auto executor = GetPK1Context().Prepare(selecter);
        auto result = executor.Execute();
        ASSERT_TRUE(CheckResult(result, {
            test_entities::EntityPK1{ 1, "1" },
        }));
    }

    //Use with multiple columns primary key
    {
        auto selecter = PK2Context::MakeSelecter()
            .Where(PK2Table.PrimaryKey == std::make_tuple(2, "2"));
        auto executor = GetPK2Context().Prepare(selecter);
        auto result = executor.Execute();
        ASSERT_TRUE(CheckResult(result, {
            test_entities::EntityPK2{ 2, "2", 20 },
        }));
    }
}


