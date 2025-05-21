#include <gtest/gtest.h>
#include <sqt/orm/expression/binder/binder_chain.h>
#include "unit_test/data_context_test_fixture.h"

class BinderChainTest : public DataContextTestFixture {

};


TEST_F(BinderChainTest, BindAllFromEntity) {

    constexpr auto updater = NoPKContext::MakeUpdater(
        NoPKTable.ID = sqt::_, 
        NoPKTable.Name = sqt::_
    ).Where(NoPKTable.ID == sqt::_);

    test_entities::EntityNoPK entity;
    entity.id = 2;
    entity.name = "FIVE";

    auto executor = GetNoPKContext().Prepare(updater);
    executor.BeginBindings().BindAllFromEntity(entity);
    executor.Execute();

    ASSERT_TRUE(CheckData({
        test_entities::EntityNoPK{ 1, "1" },
        test_entities::EntityNoPK{ 2, "FIVE" },
        test_entities::EntityNoPK{ 3, "3" },
    }));
}