#include "db_test_fixture.h"
#include "test_environment.h"

void DBTestFixture::SetUp() {

    db_path_ = MakeTempFilePath("UnitTest.db");
    std::filesystem::remove(db_path_);

    db_ = std::make_shared<sqt::Database>(sqt::Database::Open(db_path_));
}