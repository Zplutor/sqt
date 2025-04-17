#pragma once

#include <gtest/gtest.h>
#include <sqt/orm/data_context.h>
#include <sqt/orm/querier/bindable_querier_type.h>
#include <sqt/orm/table_mapping.h>
#include "unit_test/fixture/test_entities.h"

TEST(BindableQuerierTypeTest, Check) {

    using Context = sqt::DataContext<test_entities::EntityPK1>;
    constexpr auto& table = sqt::Table<test_entities::EntityPK1>;

    //No placeholder
    {
        constexpr auto querier = Context::MakeSelecter();
        static_assert(!sqt::BindableQuerierType<decltype(querier)>);
    }

    //One placeholder
    {
        constexpr auto querier = Context::MakeSelecter().Where(table.ID == sqt::_);
        static_assert(sqt::BindableQuerierType<decltype(querier)>);
    }

    //Two placeholders
    {
        constexpr auto querier = Context::MakeSelecter().Where(
            table.ID == sqt::_ && table.Name == sqt::_);
        static_assert(sqt::BindableQuerierType<decltype(querier)>);
    }
}