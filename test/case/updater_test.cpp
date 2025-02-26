#include <gtest/gtest.h>
#include <sqt/orm/data_context.h>
#include <sqt/orm/orm_support.h>
#include "db_test_fixture.h"

namespace updater_test {
class EntityNoPK {
public:
    int id;
    std::string name;
};
SQT_TABLE_BEGIN(EntityNoPK, EntityNoPK)
SQT_COLUMN(id, id)
SQT_COLUMN(name, name)
SQT_TABLE_END
}
SQT_REGISTER(updater_test, EntityNoPK)


class UpdaterTest : public DBTestFixture {
protected:
    using NoPKContext = sqt::DataContext<updater_test::EntityNoPK>;

    static constexpr auto& NoPKTable = sqt::TableV<updater_test::EntityNoPK>;

    void SetUp() override {

        DBTestFixture::SetUp();

        no_pk_context_ = std::make_unique<NoPKContext>(DB());
        no_pk_context_->Insert(updater_test::EntityNoPK{ 1, "name1" });
        no_pk_context_->Insert(updater_test::EntityNoPK{ 2, "name2" });
        no_pk_context_->Insert(updater_test::EntityNoPK{ 3, "name3" });
    }

    NoPKContext& GetNoPKContext() {
        return *no_pk_context_;
    }

private:
    std::unique_ptr<NoPKContext> no_pk_context_;
};


TEST_F(UpdaterTest, EntityUpdater) {

    constexpr auto updater = NoPKContext::MakeUpdater();
    auto executer = GetNoPKContext().Prepare(updater);
    executer.BeginBind().Bind(updater_test::EntityNoPK{ 3, "name3" });
    executer.Execute();

    auto statement = DB()->PrepareStatement("select * from EntityNoPK");

    for (std::size_t count = 0; count < 3; ++count) {
        ASSERT_TRUE(statement.Step());
        ASSERT_EQ(statement.GetColumnInt(0), 3);
        ASSERT_EQ(statement.GetColumnText(1), "name3");
    }
    ASSERT_FALSE(statement.Step());
}


TEST_F(UpdaterTest, EntityUpdater_Where) {

    constexpr auto updater = NoPKContext::MakeUpdater().Where(NoPKTable.id == 2);

    auto executer = GetNoPKContext().Prepare(updater);
    executer.BeginBind().Bind(updater_test::EntityNoPK{ 4, "name4" });
    executer.Execute();

    auto statement = DB()->PrepareStatement("select * from EntityNoPK");
    ASSERT_TRUE(statement.Step());
    ASSERT_EQ(statement.GetColumnInt(0), 1);
    ASSERT_EQ(statement.GetColumnText(1), "name1");

    ASSERT_TRUE(statement.Step());
    ASSERT_EQ(statement.GetColumnInt(0), 4);
    ASSERT_EQ(statement.GetColumnText(1), "name4");

    ASSERT_TRUE(statement.Step());
    ASSERT_EQ(statement.GetColumnInt(0), 3);
    ASSERT_EQ(statement.GetColumnText(1), "name3");

    ASSERT_FALSE(statement.Step());
}


TEST_F(UpdaterTest, ColumnUpdater_OneColumn) {

    constexpr auto updater = NoPKContext::MakeUpdater(NoPKTable.id = 9);

    auto executor = GetNoPKContext().Prepare(updater);
    executor.Execute();

    auto statement = DB()->PrepareStatement("select * from EntityNoPK");
    ASSERT_TRUE(statement.Step());
    ASSERT_EQ(statement.GetColumnInt(0), 9);
    ASSERT_EQ(statement.GetColumnText(1), "name1");

    ASSERT_TRUE(statement.Step());
    ASSERT_EQ(statement.GetColumnInt(0), 9);
    ASSERT_EQ(statement.GetColumnText(1), "name2");

    ASSERT_TRUE(statement.Step());
    ASSERT_EQ(statement.GetColumnInt(0), 9);
    ASSERT_EQ(statement.GetColumnText(1), "name3");

    ASSERT_FALSE(statement.Step());
}


TEST_F(UpdaterTest, ColumnUpdater_TwoColumns) {

    auto updater = NoPKContext::MakeUpdater(NoPKTable.id = 8, NoPKTable.name = "name8");

    auto executor = GetNoPKContext().Prepare(updater);
    executor.Execute();

    auto statement = DB()->PrepareStatement("select * from EntityNoPK");
    for (std::size_t count = 0; count < 3; ++count) {
        ASSERT_TRUE(statement.Step());
        ASSERT_EQ(statement.GetColumnInt(0), 8);
        ASSERT_EQ(statement.GetColumnText(1), "name8");
    }
    ASSERT_FALSE(statement.Step());
}