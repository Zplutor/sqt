#include "unit_test/data_context_test_fixture.h"
#include <sqt/foundation/sql_error.h>

class DataContextInsertTest : public DataContextTestFixture {

};


TEST_F(DataContextInsertTest, Insert_NoPK) {

    auto& context = GetNoPKContext();
    auto row_id = context.Insert(test_entities::EntityNoPK{ 1, "1" });
    ASSERT_EQ(row_id, 4);
    row_id = context.Insert(test_entities::EntityNoPK{ 1, "1" });
    ASSERT_EQ(row_id, 5);

    ASSERT_TRUE(CheckData({
        test_entities::EntityNoPK{ 1, "1" },
        test_entities::EntityNoPK{ 2, "2" },
        test_entities::EntityNoPK{ 3, "3" },
        test_entities::EntityNoPK{ 1, "1" },
        test_entities::EntityNoPK{ 1, "1" },
    }));
}


TEST_F(DataContextInsertTest, Insert_PK) {

    //Single column pk
    {
        auto& context = GetPK1Context();
        ASSERT_THROW(context.Insert(test_entities::EntityPK1{ 1, "10" }), sqt::SQLError);

        auto row_id = context.Insert(test_entities::EntityPK1{ 4, "4" });
        ASSERT_EQ(row_id, 4);
        ASSERT_TRUE(CheckData({
            test_entities::EntityPK1{ 1, "1" },
            test_entities::EntityPK1{ 2, "2" },
            test_entities::EntityPK1{ 3, "3" },
            test_entities::EntityPK1{ 4, "4" },
        }));
    }

    //Multiple columns pk
    {
        auto& context = GetPK2Context();
        ASSERT_THROW(context.Insert(test_entities::EntityPK2{ 1, "1", 10 }), sqt::SQLError);

        auto row_id = context.Insert(test_entities::EntityPK2{ 4, "4", 40 });
        ASSERT_EQ(row_id, 4);
        ASSERT_TRUE(CheckData({
            test_entities::EntityPK2{ 1, "1", 10 },
            test_entities::EntityPK2{ 2, "2", 20 },
            test_entities::EntityPK2{ 3, "3", 30 },
            test_entities::EntityPK2{ 4, "4", 40 },
        }));
    }
}


TEST_F(DataContextInsertTest, Replace_NoPK) {

    auto& context = GetNoPKContext();
    auto row_id = context.Replace(test_entities::EntityNoPK{ 1, "1" });
    ASSERT_EQ(row_id, 4);
    row_id = context.Replace(test_entities::EntityNoPK{ 1, "1" });
    ASSERT_EQ(row_id, 5);

    ASSERT_TRUE(CheckData({
        test_entities::EntityNoPK{ 1, "1" },
        test_entities::EntityNoPK{ 2, "2" },
        test_entities::EntityNoPK{ 3, "3" },
        test_entities::EntityNoPK{ 1, "1" },
        test_entities::EntityNoPK{ 1, "1" },
    }));
}


TEST_F(DataContextInsertTest, Replace_PK) {

    //Single column pk
    {
        auto& context = GetPK1Context();
        auto row_id = context.Replace(test_entities::EntityPK1{ 1, "10" });
        ASSERT_EQ(row_id, 1);
        row_id = context.Replace(test_entities::EntityPK1{ 4, "4" });
        ASSERT_EQ(row_id, 4);
        ASSERT_TRUE(CheckData({
            test_entities::EntityPK1{ 1, "10" },
            test_entities::EntityPK1{ 2, "2" },
            test_entities::EntityPK1{ 3, "3" },
            test_entities::EntityPK1{ 4, "4" },
        }));
    }

    //Multiple columns pk
    {
        auto& context = GetPK2Context();
        auto row_id = context.Replace(test_entities::EntityPK2{ 1, "1", 100 });
        ASSERT_EQ(row_id, 4);
        row_id = context.Replace(test_entities::EntityPK2{ 4, "4", 100 });
        ASSERT_EQ(row_id, 5);
        ASSERT_TRUE(CheckData({
            test_entities::EntityPK2{ 2, "2", 20 },
            test_entities::EntityPK2{ 3, "3", 30 },
            //The rowid is changed after replacing.
            test_entities::EntityPK2{ 1, "1", 100 },
            test_entities::EntityPK2{ 4, "4", 100 },
        }));
    }
}


TEST_F(DataContextInsertTest, AutoIncInsert) {

    auto& context = GetAutoIncContext();
    ASSERT_THROW(context.AutoIncInsert(test_entities::EntityAutoInc{ 1, "2" }), sqt::SQLError);

    auto row_id = context.AutoIncInsert(test_entities::EntityAutoInc{ 1, "4" });
    ASSERT_EQ(row_id, 4);
    row_id = context.AutoIncInsert(test_entities::EntityAutoInc{ 1, "5" });
    ASSERT_EQ(row_id, 5);
    ASSERT_TRUE(CheckData({
        test_entities::EntityAutoInc{ 1, "1" },
        test_entities::EntityAutoInc{ 2, "2" },
        test_entities::EntityAutoInc{ 3, "3" },
        test_entities::EntityAutoInc{ 4, "4" },
        test_entities::EntityAutoInc{ 5, "5" },
    }));
}


TEST_F(DataContextInsertTest, AutoIncReplace) {

    auto& context = GetAutoIncContext();
    auto row_id = context.AutoIncReplace(test_entities::EntityAutoInc{ 1, "1" });
    ASSERT_EQ(row_id, 4);
    row_id = context.AutoIncReplace(test_entities::EntityAutoInc{ 1, "2" });
    ASSERT_EQ(row_id, 5);
    row_id = context.AutoIncReplace(test_entities::EntityAutoInc{ 1, "4" });
    ASSERT_EQ(row_id, 6);
    row_id = context.AutoIncReplace(test_entities::EntityAutoInc{ 1, "5" });
    ASSERT_EQ(row_id, 7);

    ASSERT_TRUE(CheckData({
        test_entities::EntityAutoInc{ 3, "3" },
        test_entities::EntityAutoInc{ 4, "1" },
        test_entities::EntityAutoInc{ 5, "2" },
        test_entities::EntityAutoInc{ 6, "4" },
        test_entities::EntityAutoInc{ 7, "5" },
    }));
}