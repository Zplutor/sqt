#include <gtest/gtest.h>
#include <sqt/orm/table_definition.h>
#include <sqt/orm/table/column/value_source_type.h>
#include <sqt/orm/table/column/composite_column.h>

namespace composite_column_test {

struct Entity {
    int id{};
    std::string name;
    int age{};
};

SQT_TABLE_BEGIN(Entity, Entity)
SQT_COLUMN_FIELD(id, id)
SQT_COLUMN_FIELD(name, name)
SQT_COLUMN_FIELD(age, age)
SQT_TABLE_END

}

SQT_REGISTER(composite_column_test::Entity)

using TableT = sqt::TableT<composite_column_test::Entity>;
constexpr auto& TableV = sqt::TableV<composite_column_test::Entity>;


TEST(CompositeColumnTest, SingleColumn) {

    using TestType = sqt::CompositeColumn<TableT::idType>;
    static_assert(std::is_same_v<TestType::EntityType, composite_column_test::Entity>);
    static_assert(std::is_same_v<TestType::ValueType, int>);
    static_assert(sqt::CompositeColumnType<TestType>);

    constexpr TestType composite{ TableV.id };

    auto abstract_columns = composite.GetAbstractColumns();
    ASSERT_EQ(abstract_columns.size(), 1);
    ASSERT_EQ(abstract_columns[0]->GetName(), "id");
}


TEST(CompositeColumnTest, TwoColumns) {

    using TestType = sqt::CompositeColumn<TableT::idType, TableT::nameType>;
    static_assert(std::is_same_v<TestType::EntityType, composite_column_test::Entity>);
    static_assert(std::is_same_v<TestType::ValueType, std::tuple<int, std::string>>);
    static_assert(sqt::CompositeColumnType<TestType>);

    constexpr TestType composite{
        TableV.id, 
        TableV.name,
    };

    auto abstract_columns = composite.GetAbstractColumns();
    ASSERT_EQ(abstract_columns.size(), 2);
    ASSERT_EQ(abstract_columns[0]->GetName(), "id");
    ASSERT_EQ(abstract_columns[1]->GetName(), "name");
}


TEST(CompositeColumnTest, ThreeColumns) {

    using TestType = sqt::CompositeColumn<TableT::idType, TableT::nameType, TableT::ageType>;

    static_assert(std::is_same_v<TestType::EntityType, composite_column_test::Entity>);
    static_assert(
        std::is_same_v<TestType::ValueType,
        std::tuple<int, std::string, int>>);
    static_assert(sqt::CompositeColumnType<TestType>);

    constexpr TestType composite{
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


