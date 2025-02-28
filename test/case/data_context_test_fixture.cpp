#include "data_context_test_fixture.h"

void DataContextTestFixture::SetUp() {

    DBTestFixture::SetUp();

    no_pk_context_.emplace(DB());
    no_pk_context_->InitializeTable();

    FillNoPKContextData();
}


void DataContextTestFixture::FillNoPKContextData() {

    auto statement = DB()->PrepareStatement("insert into EntityNoPK(id, name) values(?, ?)");

    for (int index = 1; index <= 3; ++index) {

        statement.BindParameter(1, index);
        statement.BindParameter(2, std::to_string(index));
        statement.Step();
        statement.Reset();
    }
}


bool DataContextTestFixture::CheckData(
    const std::vector<data_context_test::EntityNoPK>& entities) const {

    auto statement = DB()->PrepareStatement("select * from EntityNoPK");
    for (const auto& each_entity : entities) {

        if (!statement.Step()) {
            return false;
        }

        if ((statement.GetColumnInt(0) != each_entity.id) ||
            (statement.GetColumnText(1) != each_entity.name)) {
            return false;
        }
    }

    return !statement.Step();
}