#pragma once

#include <optional>
#include <sqt/orm/data_context.h>
#include <sqt/orm/table_mapping.h>
#include "unit_test/db_test_fixture.h"
#include "unit_test/fixture/test_entities.h"

class DataContextTestFixture : public DBTestFixture {
protected:
    using NoPKContext = sqt::DataContext<test_entities::EntityNoPK>;
    using PK1Context = sqt::DataContext<test_entities::EntityPK1>;
    using PK2Context = sqt::DataContext<test_entities::EntityPK2>;
    using AutoIncContext = sqt::DataContext<test_entities::EntityAutoInc>;

    static constexpr auto& NoPKTable = sqt::TableV<test_entities::EntityNoPK>;
    static constexpr auto& PK1Table = sqt::TableV<test_entities::EntityPK1>;
    static constexpr auto& PK2Table = sqt::TableV<test_entities::EntityPK2>;
    static constexpr auto& AutoIncTable = sqt::TableV<test_entities::EntityAutoInc>;

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

    AutoIncContext& GetAutoIncContext() {
        return *auto_inc_context_;
    }

    bool CheckData(const std::vector<test_entities::EntityNoPK>& entities) const;
    bool CheckData(const std::vector<test_entities::EntityPK1>& entities) const;
    bool CheckData(const std::vector<test_entities::EntityPK2>& entities) const;
    bool CheckData(const std::vector<test_entities::EntityAutoInc>& entities) const;

private:
    void FillNoPKContextData();
    void FillPK1ContextData();
    void FillPK2ContextData();
    void FillAutoIncContextData();

private:
    std::optional<NoPKContext> no_pk_context_;
    std::optional<PK1Context> pk1_context_;
    std::optional<PK2Context> pk2_context_;
    std::optional<AutoIncContext> auto_inc_context_;
};