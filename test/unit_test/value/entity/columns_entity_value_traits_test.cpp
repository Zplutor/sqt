#include <gtest/gtest.h>
#include <sqt/orm/value/entity/columns_entity_value_traits.h>
#include <sqt/orm/value/entity/entity_value_traits_type.h>
#include "unit_test/fixture/test_entities.h"

TEST(ColumnsEntityValueTraitsTest, EntityValueTraitsType) {

    using Table = sqt::TableType<test_entities::EntityNoPK>;

    //One column
    {
        static_assert(sqt::EntityValueTraitsType<sqt::ColumnsEntityValueTraits<Table::IDType>>);
    }

    //Two columns
    {
        using Traits = sqt::ColumnsEntityValueTraits<Table::IDType, Table::NameType>;
        static_assert(sqt::EntityValueTraitsType<Traits>);
    }
}


TEST(ColumnsEntityValueTraitsTest, ManipulatingColumns) {

    using Table = sqt::TableType<test_entities::EntityNoPK>;

    //One column
    {
        constexpr sqt::ColumnsView<test_entities::EntityNoPK> columns =
            sqt::ColumnsEntityValueTraits<Table::IDType>::ManipulatingColumns;

        ASSERT_EQ(columns.size(), 1);
        ASSERT_EQ(columns[0], &Table::GetInstance().ID);
    }

    //Two columns
    {
        constexpr sqt::ColumnsView<test_entities::EntityNoPK> columns =
            sqt::ColumnsEntityValueTraits<Table::IDType, Table::NameType>::ManipulatingColumns;

        ASSERT_EQ(columns.size(), 2);
        ASSERT_EQ(columns[0], &Table::GetInstance().ID);
        ASSERT_EQ(columns[1], &Table::GetInstance().Name);
    }
}
