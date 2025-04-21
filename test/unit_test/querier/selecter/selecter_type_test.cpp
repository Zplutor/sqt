#include <gtest/gtest.h>
#include <sqt/orm/data_context.h>
#include <sqt/orm/querier/selecter/selecter_type.h>
#include <sqt/orm/table_mapping.h>
#include "unit_test/fixture/test_entities.h"

TEST(SelecterTypeTest, Check) {

    using Context = sqt::DataContext<test_entities::EntityPK1>;
    constexpr auto& table = sqt::Table<test_entities::EntityPK1>;

    //Primary selecter, all columns.
    {
        constexpr auto primary_selecter = Context::MakeSelecter();
        static_assert(sqt::SelecterType<decltype(primary_selecter)>);

        //Where
        {
            constexpr auto selecter = primary_selecter.Where(table.ID == sqt::_);
            static_assert(sqt::SelecterType<decltype(selecter)>);
        }

        //OrderBy
        {
            constexpr auto selecter = primary_selecter.OrderBy(table.ID.Desc());
            static_assert(sqt::SelecterType<decltype(selecter)>);
        }

        //Limit
        {
            constexpr auto selecter = primary_selecter.Limit(10);
            static_assert(sqt::SelecterType<decltype(selecter)>);
        }
    }

    //Primary selecter, specific columns.
    {
        constexpr auto primary_selecter = Context::MakeSelecter(table.ID);
        static_assert(sqt::SelecterType<decltype(primary_selecter)>);

        //Where
        {
            constexpr auto selecter = primary_selecter.Where(table.ID == sqt::_);
            static_assert(sqt::SelecterType<decltype(selecter)>);
        }

        //OrderBy
        {
            constexpr auto selecter = primary_selecter.OrderBy(table.ID.Desc());
            static_assert(sqt::SelecterType<decltype(selecter)>);
        }

        //Limit
        {
            constexpr auto selecter = primary_selecter.Limit(10);
            static_assert(sqt::SelecterType<decltype(selecter)>);
        }
    }
}