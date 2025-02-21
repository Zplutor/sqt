#pragma once

#include <filesystem>
#include <gtest/gtest.h>
#include <sqt/foundation/database.h>

class DBTestFixture : public testing::Test {
protected:
    void SetUp() override;

    sqt::Database& DB() {
        return *db_;
    }

private:
    std::filesystem::path db_path_;
    std::shared_ptr<sqt::Database> db_;
};