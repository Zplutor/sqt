#include <gtest/gtest.h>
#include <sqt/orm/orm_support.h>
#include <sqt/orm/table/column/value_source_type.h>
#include "unit_test/fixture/blob.h"

namespace value_source_test {

struct EntityWithField {
    std::string primitive;
    std::optional<int> nullable;
    BLOB custom;
};
SQT_TABLE_BEGIN(EntityWithField, EntityWithField)
SQT_COLUMN_FIELD(Primitive, primitive)
SQT_COLUMN_FIELD(Nullable, nullable)
SQT_COLUMN_FIELD(Custom, custom)
SQT_TABLE_END

}

SQT_REGISTER(value_source_test, EntityWithField)


TEST(ValueSourceTest, DefaultValueSource_Field) {

    using TableType = sqt::TableT<value_source_test::EntityWithField>;

    value_source_test::EntityWithField entity;
    entity.primitive = "primitive";
    entity.nullable = 101;
    entity.custom.data.assign({ std::byte(0x3), std::byte(0x1), std::byte(0x2) });

    //Primitive
    {
        using ValueSource = typename TableType::PrimitiveType::ValueSource;
        static_assert(sqt::ValueSourceType<ValueSource, value_source_test::EntityWithField>);
        static_assert(std::is_same_v<typename ValueSource::ValueType, std::string>);

        const std::string& value = ValueSource::GetValueFromEntity(entity);
        ASSERT_EQ(value, "primitive");

        ValueSource::SetValueToEntity(entity, "primitive2");
        ASSERT_EQ(entity.primitive, "primitive2");
    }

    //Nullable
    {
        using ValueSource = typename TableType::NullableType::ValueSource;
        static_assert(sqt::ValueSourceType<ValueSource, value_source_test::EntityWithField>);
        static_assert(std::is_same_v<typename ValueSource::ValueType, std::optional<int>>);

        const std::optional<int>& value = ValueSource::GetValueFromEntity(entity);
        ASSERT_EQ(value, 101);

        ValueSource::SetValueToEntity(entity, 102);
        ASSERT_EQ(entity.nullable, 102);
    }

    //Custom
    {
        using ValueSource = typename TableType::CustomType::ValueSource;
        static_assert(sqt::ValueSourceType<ValueSource, value_source_test::EntityWithField>);
        static_assert(std::is_same_v<typename ValueSource::ValueType, BLOB>);

        const BLOB& value = ValueSource::GetValueFromEntity(entity);
        ASSERT_EQ(
            value.data, 
            std::vector<std::byte>({ std::byte(0x3), std::byte(0x1), std::byte(0x2) }));

        ValueSource::SetValueToEntity(
            entity, 
            BLOB{ std::vector<std::byte>({ std::byte(0x1), std::byte(0x2), std::byte(0x3) }) });
        ASSERT_EQ(
            entity.custom.data, 
            std::vector<std::byte>({ std::byte(0x1), std::byte(0x2), std::byte(0x3) }));
    }
}