#include <gtest/gtest.h>
#include <sqt/orm/data_context.h>
#include <sqt/orm/orm_support.h>
#include "data_context_test_fixture.h"

class UpdaterTest : public DataContextTestFixture {

};


TEST_F(UpdaterTest, EntityUpdater) {

    constexpr auto updater = NoPKContext::MakeUpdater();
    auto executer = GetNoPKContext().Prepare(updater);
    executer.BeginBind().Bind(test_entities::EntityNoPK{ 3, "name3" });
    executer.Execute();

    ASSERT_TRUE(CheckData({
        test_entities::EntityNoPK{ 3, "name3" },
        test_entities::EntityNoPK{ 3, "name3" },
        test_entities::EntityNoPK{ 3, "name3" },
    }));
}


TEST_F(UpdaterTest, EntityUpdater_Where) {

    constexpr auto updater = NoPKContext::MakeUpdater().Where(NoPKTable.ID == 2);

    auto executer = GetNoPKContext().Prepare(updater);
    executer.BeginBind().Bind(test_entities::EntityNoPK{ 4, "name4" });
    executer.Execute();

    ASSERT_TRUE(CheckData({
        test_entities::EntityNoPK{ 1, "1" },
        test_entities::EntityNoPK{ 4, "name4" },
        test_entities::EntityNoPK{ 3, "3" },
    }));
}


TEST_F(UpdaterTest, NoPrimaryKeyUpdater) {

    //Single column primary key
    {
        constexpr auto updater = PK1Context::MakeNoPrimaryKeyUpdater();
        auto executer = GetPK1Context().Prepare(updater);

        executer.BeginBind().Bind(test_entities::EntityPK1{ 1, "5" });
        auto changes = executer.Execute();
        ASSERT_EQ(changes, 3);
        ASSERT_TRUE(CheckData({
            test_entities::EntityPK1{ 1, "5" },
            test_entities::EntityPK1{ 2, "5" },
            test_entities::EntityPK1{ 3, "5" },
        }));
    }

    //Multiple column primary key
    {
        constexpr auto updater = PK2Context::MakeNoPrimaryKeyUpdater();
        auto executer = GetPK2Context().Prepare(updater);

        executer.BeginBind().Bind(test_entities::EntityPK2{ 1, "1", 50 });
        auto changes = executer.Execute();
        ASSERT_EQ(changes, 3);
        ASSERT_TRUE(CheckData({
            test_entities::EntityPK2{ 1, "1", 50 },
            test_entities::EntityPK2{ 2, "2", 50 },
            test_entities::EntityPK2{ 3, "3", 50 },
        }));
    }
}


TEST_F(UpdaterTest, ColumnUpdater_OneColumn) {

    constexpr auto updater = NoPKContext::MakeUpdater(NoPKTable.ID = 9);

    auto executor = GetNoPKContext().Prepare(updater);
    executor.Execute();

    ASSERT_TRUE(CheckData({
        test_entities::EntityNoPK{ 9, "1" },
        test_entities::EntityNoPK{ 9, "2" },
        test_entities::EntityNoPK{ 9, "3" },
    }));
}


TEST_F(UpdaterTest, ColumnUpdater_TwoColumns) {

    auto updater = NoPKContext::MakeUpdater(NoPKTable.ID = 8, NoPKTable.Name = "name8");

    auto executor = GetNoPKContext().Prepare(updater);
    executor.Execute();

    ASSERT_TRUE(CheckData({
        test_entities::EntityNoPK{ 8, "name8" },
        test_entities::EntityNoPK{ 8, "name8" },
        test_entities::EntityNoPK{ 8, "name8" },
    }));
}


TEST_F(UpdaterTest, ColumnUpdater_Where) {

    constexpr auto updater = NoPKContext::MakeUpdater(NoPKTable.ID = 10).Where(NoPKTable.ID == 1);

    auto executor = GetNoPKContext().Prepare(updater);
    executor.Execute();

    ASSERT_TRUE(CheckData({
        test_entities::EntityNoPK{ 10, "1" },
        test_entities::EntityNoPK{ 2, "2" },
        test_entities::EntityNoPK{ 3, "3" },
    }));
}


TEST_F(UpdaterTest, DataContext_Update) {

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