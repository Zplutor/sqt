#include <gtest/gtest.h>
#include <sqt/orm/column/composite_column.h>
#include <sqt/orm/orm_support.h>

namespace composite_column_test {

struct Entity {
    int id{};
    std::string name;
    int age{};
};

SQT_TABLE_BEGIN(Entity, Entity)
SQT_COLUMN(id, id)
SQT_COLUMN(name, name)
SQT_COLUMN(age, age)
SQT_TABLE_END

}

SQT_REGISTER(composite_column_test, Entity)

using TableT = sqt::TableT<composite_column_test::Entity>;
constexpr auto& TableV = sqt::TableV<composite_column_test::Entity>;


TEST(CompositeColumnTest, SingleColumn) {

    using CompositeColumnType = sqt::CompositeColumn<TableT::idType>;
    static_assert(std::is_same_v<CompositeColumnType::EntityType, composite_column_test::Entity>);
    static_assert(std::is_same_v<CompositeColumnType::ValueType, int>);

    constexpr CompositeColumnType composite{ TableV.id };

    auto abstract_columns = composite.GetAbstractColumns();
    ASSERT_EQ(abstract_columns.size(), 1);
    ASSERT_EQ(abstract_columns[0]->GetName(), "id");
}


TEST(CompositeColumnTest, TwoColumns) {

    using CompositeColumnType = sqt::CompositeColumn<TableT::idType, TableT::nameType>;
    static_assert(std::is_same_v<CompositeColumnType::EntityType, composite_column_test::Entity>);
    static_assert(std::is_same_v<CompositeColumnType::ValueType, std::tuple<int, std::string>>);

    constexpr CompositeColumnType composite{
        TableV.id, 
        TableV.name,
    };

    auto abstract_columns = composite.GetAbstractColumns();
    ASSERT_EQ(abstract_columns.size(), 2);
    ASSERT_EQ(abstract_columns[0]->GetName(), "id");
    ASSERT_EQ(abstract_columns[1]->GetName(), "name");
}


TEST(CompositeColumnTest, ThreeColumns) {

    using CompositeColumnType = 
        sqt::CompositeColumn<TableT::idType, TableT::nameType, TableT::ageType>;

    static_assert(std::is_same_v<CompositeColumnType::EntityType, composite_column_test::Entity>);
    static_assert(
        std::is_same_v<CompositeColumnType::ValueType, 
        std::tuple<int, std::string, int>>);

    constexpr CompositeColumnType composite{
        TableV.id,
        TableV.name,
        TableV.age,
    };

    auto abstract_columns = composite.GetAbstractColumns();
    ASSERT_EQ(abstract_columns.size(), 3);
    ASSERT_EQ(abstract_columns[0]->GetName(), "id");
    ASSERT_EQ(abstract_columns[1]->GetName(), "name");
    ASSERT_EQ(abstract_columns[2]->GetName(), "age");
}


TEST(CompositeColumnTest, MakeCompositeColumn) {

    auto single_column = sqt::MakeCompositeColumn(TableV.id);
    static_assert(std::is_same_v<decltype(single_column), sqt::CompositeColumn<TableT::idType>>);

    auto two_columns = sqt::MakeCompositeColumn(TableV.id, TableV.name);
    static_assert(
        std::is_same_v<decltype(two_columns), 
        sqt::CompositeColumn<TableT::idType, TableT::nameType>>);

    auto three_columns = sqt::MakeCompositeColumn(TableV.id, TableV.name, TableV.age);
    static_assert(
        std::is_same_v<decltype(three_columns),
        sqt::CompositeColumn<TableT::idType, TableT::nameType, TableT::ageType>>);
}