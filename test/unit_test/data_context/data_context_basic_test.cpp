#include <gtest/gtest.h>
#include <sqt/foundation/database.h>
#include <sqt/orm/data_context.h>
#include <sqt/orm/orm_support.h>
#include "test_environment.h"

struct DataContextBasicTestEntity {
    int id{};
};
SQT_TABLE_BEGIN(DataContextBasicTestEntity, DataContextBasicTestEntity)
SQT_COLUMN(ID, id)
SQT_TABLE_END
SQT_REGISTER(, DataContextBasicTestEntity)

using TestDataContext = sqt::DataContext<DataContextBasicTestEntity>;
static_assert(!std::copyable<TestDataContext>);
static_assert(!std::movable<TestDataContext>);


class DataContextBasicTest : public testing::Test {
protected:
    void SetUp() override {
        db_path_ = MakeTempFilePath("DataContextBasicTest.db");
        std::filesystem::remove(db_path_);
    }

    const std::filesystem::path& DBPath() const {
        return db_path_;
    }

private:
    std::filesystem::path db_path_;
};


TEST_F(DataContextBasicTest, Constructor) {

    //Construct from a non-shared database.
    {
        sqt::Database db = sqt::Database::Open(DBPath());
        TestDataContext data_context{ std::move(db) };
        ASSERT_NE(data_context.Database(), nullptr);
    }

    //Construct from a shared database.
    {
        auto db = std::make_shared<sqt::Database>(sqt::Database::Open(DBPath()));
        TestDataContext data_context{ db };
        ASSERT_EQ(data_context.Database(), db);
    }
}


TEST_F(DataContextBasicTest, GetDatabase) {

    TestDataContext data_context{ sqt::Database::Open(DBPath()) };

    auto db = data_context.Database();
    ASSERT_NE(db, nullptr);

    //Getting the database won't initialize the table.
    auto table_info = db->GetTableInfo("DataContextBasicTestEntity");
    ASSERT_FALSE(table_info.has_value());
}


TEST_F(DataContextBasicTest, InitializeTable) {

    TestDataContext data_context{ sqt::Database::Open(DBPath()) };

    //Initialize the table manually.
    data_context.InitializeTable();

    //Initialize the table again won't throw any exception.
    ASSERT_NO_THROW(data_context.InitializeTable());

    auto db = data_context.Database();
    auto table_info = db->GetTableInfo("DataContextBasicTestEntity");
    ASSERT_TRUE(table_info.has_value());
}