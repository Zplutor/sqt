#include "db_test_fixture.h"

void DBTestFixture::SetUp() {

    db_path_ = "test_data\\test.db";
    std::filesystem::remove(db_path_);

    db_ = std::make_shared<sqt::Database>(sqt::Database::Open(db_path_));
}