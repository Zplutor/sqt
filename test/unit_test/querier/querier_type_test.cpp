#include <gtest/gtest.h>
#include <sqt/orm/data_context.h>
#include <sqt/orm/querier/querier_type.h>
#include <sqt/orm/table_mapping.h>
#include "unit_test/fixture/test_entities.h"

TEST(QuerierTypeTest, Inserters) {

    using Context = sqt::DataContext<test_entities::EntityAutoInc>;
    constexpr auto& table = sqt::Table<test_entities::EntityAutoInc>;

    {
        constexpr auto inserter = Context::MakeInserter();
        static_assert(sqt::QuerierType<decltype(inserter)>);
    }

    {
        constexpr auto inserter = Context::MakeReplacer();
        static_assert(sqt::QuerierType<decltype(inserter)>);
    }

    {
        constexpr auto inserter = Context::MakeInserter(table.id = sqt::_);
        static_assert(sqt::QuerierType<decltype(inserter)>);
    }

    {
        constexpr auto inserter = Context::MakeReplacer(table.id = sqt::_);
        static_assert(sqt::QuerierType<decltype(inserter)>);
    }

    {
        constexpr auto inserter = Context::MakeAutoIncInserter();
        static_assert(sqt::QuerierType<decltype(inserter)>);
    }

    {
        constexpr auto inserter = Context::MakeAutoIncReplacer();
        static_assert(sqt::QuerierType<decltype(inserter)>);
    }
}


TEST(QuerierTypeTest, Updaters) {

    using Context = sqt::DataContext<test_entities::EntityAutoInc>;
    constexpr auto& table = sqt::Table<test_entities::EntityAutoInc>;

    {
        constexpr auto updater = Context::MakeUpdater();
        static_assert(sqt::QuerierType<decltype(updater)>);
    }

    {
        constexpr auto updater = Context::MakeUpdater(table.id = sqt::_);
        static_assert(sqt::QuerierType<decltype(updater)>);
    }

    {
        constexpr auto updater = Context::MakeNoPrimaryKeyUpdater();
        static_assert(sqt::QuerierType<decltype(updater)>);
    }
}


TEST(QuerierTypeTest, Deleters) {

    using Context = sqt::DataContext<test_entities::EntityAutoInc>;
    constexpr auto& table = sqt::Table<test_entities::EntityAutoInc>;

    {
        constexpr auto deleter = Context::MakeDeleter();
        static_assert(sqt::QuerierType<decltype(deleter)>);
    }
}


TEST(QuerierTypeTest, Selecters) {

    using Context = sqt::DataContext<test_entities::EntityAutoInc>;
    constexpr auto& table = sqt::Table<test_entities::EntityAutoInc>;

    //Primary selecter, all columns.
    {
        constexpr auto primary_selecter = Context::MakeSelecter();
        static_assert(sqt::QuerierType<decltype(primary_selecter)>);

        //Where
        {
            constexpr auto selecter = primary_selecter.Where(table.id == sqt::_);
            static_assert(sqt::QuerierType<decltype(selecter)>);
        }

        //OrderBy
        {
            constexpr auto selecter = primary_selecter.OrderBy(table.id.Desc());
            static_assert(sqt::QuerierType<decltype(selecter)>);
        }

        //Limit
        {
            constexpr auto selecter = primary_selecter.Limit(10);
            static_assert(sqt::QuerierType<decltype(selecter)>);
        }
    }

    
    //Primary selecter, specific columns.
    {
        constexpr auto primary_selecter = Context::MakeSelecter(table.id);
        static_assert(sqt::QuerierType<decltype(primary_selecter)>);

        //Where
        {
            constexpr auto selecter = primary_selecter.Where(table.id == sqt::_);
            static_assert(sqt::QuerierType<decltype(selecter)>);
        }

        //OrderBy
        {
            constexpr auto selecter = primary_selecter.OrderBy(table.id.Desc());
            static_assert(sqt::QuerierType<decltype(selecter)>);
        }

        //Limit
        {
            constexpr auto selecter = primary_selecter.Limit(10);
            static_assert(sqt::QuerierType<decltype(selecter)>);
        }
    }
}