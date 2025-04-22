#include <gtest/gtest.h>
#include <sqt/orm/data_context.h>
#include <sqt/orm/table_mapping.h>
#include "unit_test/fixture/test_entities.h"
#include "unit_test/data_context_test_fixture.h"

class IteratorTest : public DataContextTestFixture {

};


TEST_F(IteratorTest, CheckInputIterator) {

    {
        constexpr auto selecter = NoPKContext::MakeSelecter();
        using Iterator = sqt::Iterator<decltype(selecter)>;
        static_assert(std::input_iterator<Iterator>);
    }

    {
        constexpr auto selecter = NoPKContext::MakeSelecter(NoPKTable.ID, NoPKTable.Name);
        using Iterator = sqt::Iterator<decltype(selecter)>;
        static_assert(std::input_iterator<Iterator>);
    }
}
