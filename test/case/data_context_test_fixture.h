#pragma once

#include <optional>
#include <sqt/orm/data_context.h>
#include <sqt/orm/orm_support.h>
#include <sqt/orm/table_mapping.h>
#include "db_test_fixture.h"

namespace data_context_test {

/**
Entity without primary key.
*/
struct EntityNoPK {
    int id{};
    std::string name;
    friend auto operator<=>(const EntityNoPK&, const EntityNoPK&) = default;
};
SQT_TABLE_BEGIN(EntityNoPK, EntityNoPK)
SQT_COLUMN(ID, id)
SQT_COLUMN(Name, name)
SQT_TABLE_END
}
SQT_REGISTER(data_context_test, EntityNoPK)


class DataContextTestFixture : public DBTestFixture {
protected:
    using NoPKContext = sqt::DataContext<data_context_test::EntityNoPK>;

    static constexpr auto& NoPKTable = sqt::TableV<data_context_test::EntityNoPK>;

    void SetUp() override;

    NoPKContext& GetNoPKContext() {
        return *no_pk_context_;
    }

    bool CheckData(const std::vector<data_context_test::EntityNoPK>& entities) const;

private:
    void FillNoPKContextData();

private:
    std::optional<NoPKContext> no_pk_context_;
};