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


/**
Entity with single column primary key.
*/
struct EntityPK1 {
    int id{};
    std::string name;
    friend auto operator<=>(const EntityPK1&, const EntityPK1&) = default;
};
SQT_TABLE_BEGIN(EntityPK1, EntityPK1)
SQT_COLUMN(ID, id)
SQT_COLUMN(Name, name)
SQT_PRIMARY_KEY(ID)
SQT_TABLE_END


/**
Entity with multiple column primary key.
*/
struct EntityPK2 {
    int id{};
    std::string name;
    int age{};
    friend auto operator<=>(const EntityPK2&, const EntityPK2&) = default;
};
SQT_TABLE_BEGIN(EntityPK2, EntityPK2)
SQT_COLUMN(ID, id)
SQT_COLUMN(Name, name)
SQT_COLUMN(Age, age)
SQT_PRIMARY_KEY(ID, Name)
SQT_TABLE_END
}

SQT_REGISTER(data_context_test, EntityNoPK)
SQT_REGISTER(data_context_test, EntityPK1)
SQT_REGISTER(data_context_test, EntityPK2)


class DataContextTestFixture : public DBTestFixture {
protected:
    using NoPKContext = sqt::DataContext<data_context_test::EntityNoPK>;
    using PK1Context = sqt::DataContext<data_context_test::EntityPK1>;
    using PK2Context = sqt::DataContext<data_context_test::EntityPK2>;

    static constexpr auto& NoPKTable = sqt::TableV<data_context_test::EntityNoPK>;
    static constexpr auto& PK1Table = sqt::TableV<data_context_test::EntityPK1>;
    static constexpr auto& PK2Table = sqt::TableV<data_context_test::EntityPK2>;

    void SetUp() override;

    NoPKContext& GetNoPKContext() {
        return *no_pk_context_;
    }

    PK1Context& GetPK1Context() {
        return *pk1_context_;
    }

    PK2Context& GetPK2Context() {
        return *pk2_context_;
    }

    bool CheckData(const std::vector<data_context_test::EntityNoPK>& entities) const;
    bool CheckData(const std::vector<data_context_test::EntityPK1>& entities) const;
    bool CheckData(const std::vector<data_context_test::EntityPK2>& entities) const;

private:
    void FillNoPKContextData();
    void FillPK1ContextData();
    void FillPK2ContextData();

private:
    std::optional<NoPKContext> no_pk_context_;
    std::optional<PK1Context> pk1_context_;
    std::optional<PK2Context> pk2_context_;
};