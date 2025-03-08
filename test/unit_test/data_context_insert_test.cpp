#include "unit_test/data_context_test_fixture.h"
#include <sqt/foundation/sql_error.h>

class DataContextInsertTest : public DataContextTestFixture {

};


TEST_F(DataContextInsertTest, Insert_NoPK) {

    auto& context = GetNoPKContext();
    context.Insert(test_entities::EntityNoPK{ 1, "1" });
    context.Insert(test_entities::EntityNoPK{ 1, "1" });

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

        context.Insert(test_entities::EntityPK1{ 4, "4" });
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

        context.Insert(test_entities::EntityPK2{ 4, "4", 40 });
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
    context.Replace(test_entities::EntityNoPK{ 1, "1" });
    context.Replace(test_entities::EntityNoPK{ 1, "1" });

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
        context.Replace(test_entities::EntityPK1{ 1, "10" });
        context.Replace(test_entities::EntityPK1{ 4, "4" });
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
        context.Replace(test_entities::EntityPK2{ 1, "1", 100 });
        context.Replace(test_entities::EntityPK2{ 4, "4", 100 });
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

    context.AutoIncInsert(test_entities::EntityAutoInc{ 1, "4" });
    context.AutoIncInsert(test_entities::EntityAutoInc{ 1, "5" });
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
    context.AutoIncReplace(test_entities::EntityAutoInc{ 1, "1" });
    context.AutoIncReplace(test_entities::EntityAutoInc{ 1, "2" });
    context.AutoIncReplace(test_entities::EntityAutoInc{ 1, "4" });
    context.AutoIncReplace(test_entities::EntityAutoInc{ 1, "5" });

    ASSERT_TRUE(CheckData({
        test_entities::EntityAutoInc{ 3, "3" },
        test_entities::EntityAutoInc{ 4, "1" },
        test_entities::EntityAutoInc{ 5, "2" },
        test_entities::EntityAutoInc{ 6, "4" },
        test_entities::EntityAutoInc{ 7, "5" },
    }));
}