#include <gtest/gtest.h>
#include <sqt/orm/data_context.h>
#include <sqt/orm/orm_support.h>
#include "db_test_fixture.h"

class UpdaterTest : public DBTestFixture {

};

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

TEST_F(UpdaterTest, EntityUpdater) {

    using Context = sqt::DataContext<updater_test::EntityNoPK>;

    Context context{ DB() };
    context.Insert(updater_test::EntityNoPK{ 1, "name1" });
    context.Insert(updater_test::EntityNoPK{ 2, "name2" });

    constexpr auto updater = Context::MakeUpdater();
    auto executer = context.Prepare(updater);
    executer.BeginBind().Bind(updater_test::EntityNoPK{ 3, "name3" });
    executer.Execute();

    auto statement = DB()->PrepareStatement("select * from EntityNoPK");
    ASSERT_TRUE(statement.Step());
    ASSERT_EQ(statement.GetColumnInt(0), 3);
    ASSERT_EQ(statement.GetColumnText(1), "name3");

    ASSERT_TRUE(statement.Step());
    ASSERT_EQ(statement.GetColumnInt(0), 3);
    ASSERT_EQ(statement.GetColumnText(1), "name3");

    ASSERT_FALSE(statement.Step());
}


TEST_F(UpdaterTest, EntityUpdater_Where) {

    using Context = sqt::DataContext<updater_test::EntityNoPK>;

    Context context{ DB() };
    context.Insert(updater_test::EntityNoPK{ 1, "name1" });
    context.Insert(updater_test::EntityNoPK{ 2, "name2" });

    constexpr auto& table = sqt::TableV<updater_test::EntityNoPK>;
    constexpr auto updater = Context::MakeUpdater().Where(table.id == 2);

    auto executer = context.Prepare(updater);
    executer.BeginBind().Bind(updater_test::EntityNoPK{ 4, "name4" });
    executer.Execute();

    auto statement = DB()->PrepareStatement("select * from EntityNoPK");
    ASSERT_TRUE(statement.Step());
    ASSERT_EQ(statement.GetColumnInt(0), 1);
    ASSERT_EQ(statement.GetColumnText(1), "name1");

    ASSERT_TRUE(statement.Step());
    ASSERT_EQ(statement.GetColumnInt(0), 4);
    ASSERT_EQ(statement.GetColumnText(1), "name4");

    ASSERT_FALSE(statement.Step());
}