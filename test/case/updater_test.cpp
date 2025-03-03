#include <gtest/gtest.h>
#include <sqt/orm/data_context.h>
#include <sqt/orm/orm_support.h>
#include "data_context_test_fixture.h"

class UpdaterTest : public DataContextTestFixture {

};


TEST_F(UpdaterTest, EntityUpdater) {

    constexpr auto updater = NoPKContext::MakeUpdater();
    auto executer = GetNoPKContext().Prepare(updater);
    executer.BeginBind().Bind(data_context_test::EntityNoPK{ 3, "name3" });
    executer.Execute();

    ASSERT_TRUE(CheckData({
        data_context_test::EntityNoPK{ 3, "name3" },
        data_context_test::EntityNoPK{ 3, "name3" },
        data_context_test::EntityNoPK{ 3, "name3" },
    }));
}


TEST_F(UpdaterTest, EntityUpdater_Where) {

    constexpr auto updater = NoPKContext::MakeUpdater().Where(NoPKTable.ID == 2);

    auto executer = GetNoPKContext().Prepare(updater);
    executer.BeginBind().Bind(data_context_test::EntityNoPK{ 4, "name4" });
    executer.Execute();

    ASSERT_TRUE(CheckData({
        data_context_test::EntityNoPK{ 1, "1" },
        data_context_test::EntityNoPK{ 4, "name4" },
        data_context_test::EntityNoPK{ 3, "3" },
    }));
}


TEST_F(UpdaterTest, ColumnUpdater_OneColumn) {

    constexpr auto updater = NoPKContext::MakeUpdater(NoPKTable.ID = 9);

    auto executor = GetNoPKContext().Prepare(updater);
    executor.Execute();

    ASSERT_TRUE(CheckData({
        data_context_test::EntityNoPK{ 9, "1" },
        data_context_test::EntityNoPK{ 9, "2" },
        data_context_test::EntityNoPK{ 9, "3" },
    }));
}


TEST_F(UpdaterTest, ColumnUpdater_TwoColumns) {

    auto updater = NoPKContext::MakeUpdater(NoPKTable.ID = 8, NoPKTable.Name = "name8");

    auto executor = GetNoPKContext().Prepare(updater);
    executor.Execute();

    ASSERT_TRUE(CheckData({
        data_context_test::EntityNoPK{ 8, "name8" },
        data_context_test::EntityNoPK{ 8, "name8" },
        data_context_test::EntityNoPK{ 8, "name8" },
    }));
}


TEST_F(UpdaterTest, ColumnUpdater_Where) {

    constexpr auto updater = NoPKContext::MakeUpdater(NoPKTable.ID = 10).Where(NoPKTable.ID == 1);

    auto executor = GetNoPKContext().Prepare(updater);
    executor.Execute();

    ASSERT_TRUE(CheckData({
        data_context_test::EntityNoPK{ 10, "1" },
        data_context_test::EntityNoPK{ 2, "2" },
        data_context_test::EntityNoPK{ 3, "3" },
    }));
}