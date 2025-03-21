#include <gtest/gtest.h>
#include <sqt/orm/table_definition.h>
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
SQT_REGISTER(value_source_test::EntityWithField)

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
        static_assert(std::is_same_v<
            decltype(ValueSource::GetValueFromEntity(entity)),
            const std::string&>);

        const auto& value = ValueSource::GetValueFromEntity(entity);
        ASSERT_EQ(value, "primitive");

        ValueSource::SetValueToEntity(entity, "primitive2");
        ASSERT_EQ(entity.primitive, "primitive2");
    }

    //Nullable
    {
        using ValueSource = typename TableType::NullableType::ValueSource;
        static_assert(sqt::ValueSourceType<ValueSource, value_source_test::EntityWithField>);
        static_assert(std::is_same_v<typename ValueSource::ValueType, std::optional<int>>);
        static_assert(std::is_same_v<
            decltype(ValueSource::GetValueFromEntity(entity)),
            const std::optional<int>&>);

        const auto& value = ValueSource::GetValueFromEntity(entity);
        ASSERT_EQ(value, 101);

        ValueSource::SetValueToEntity(entity, 102);
        ASSERT_EQ(entity.nullable, 102);
    }

    //Custom
    {
        using ValueSource = typename TableType::CustomType::ValueSource;
        static_assert(sqt::ValueSourceType<ValueSource, value_source_test::EntityWithField>);
        static_assert(std::is_same_v<typename ValueSource::ValueType, BLOB>);
        static_assert(std::is_same_v<
            decltype(ValueSource::GetValueFromEntity(entity)),
            const BLOB&>);

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


namespace value_source_test {
struct EntityWithAccessor {
    const std::string& GetValueRef() const {
        return value;
    }
    std::string GetValueCopy() const {
        return value;
    }
    void SetValue(std::string value) {
        this->value = std::move(value);
    }
    std::string value;
};
SQT_TABLE_BEGIN(EntityWithAccessor, EntityWithAccessor)
SQT_COLUMN_ACCESSOR(ValueRef, GetValueRef, SetValue)
SQT_COLUMN_ACCESSOR(ValueCopy, GetValueCopy, SetValue)
SQT_TABLE_END
}
SQT_REGISTER(value_source_test::EntityWithAccessor)

TEST(ValueSourceTest, DefaultValueSource_Accessor) {

    using TableType = sqt::TableT<value_source_test::EntityWithAccessor>;
    value_source_test::EntityWithAccessor entity;
    entity.value = "value";

    //ValueRef
    {
        using ValueSource = typename TableType::ValueRefType::ValueSource;
        static_assert(sqt::ValueSourceType<ValueSource, value_source_test::EntityWithAccessor>);
        static_assert(std::is_same_v<typename ValueSource::ValueType, std::string>);
        static_assert(std::is_same_v<
            decltype(ValueSource::GetValueFromEntity(entity)), 
            const std::string&>);

        const std::string& value = ValueSource::GetValueFromEntity(entity);
        ASSERT_EQ(value, "value");

        ValueSource::SetValueToEntity(entity, "value2");
        ASSERT_EQ(entity.value, "value2");
    }

    //ValueCopy
    {
        using ValueSource = typename TableType::ValueCopyType::ValueSource;
        static_assert(sqt::ValueSourceType<ValueSource, value_source_test::EntityWithAccessor>);
        static_assert(std::is_same_v<typename ValueSource::ValueType, std::string>);
        static_assert(std::is_same_v<
            decltype(ValueSource::GetValueFromEntity(entity)),
            std::string>);

        auto value = ValueSource::GetValueFromEntity(entity);
        ASSERT_EQ(value, "value2");

        ValueSource::SetValueToEntity(entity, "value3");
        ASSERT_EQ(entity.value, "value3");
    }
}


namespace value_source_test {
struct EntityCustom {
    std::string value;
};
class CustomValueSource {
public:
    using ValueType = std::string;
    static const std::string& GetValueFromEntity(const EntityCustom& entity) {
        return entity.value;
    }
    static void SetValueToEntity(EntityCustom& entity, std::string value) {
        entity.value = std::move(value);
    }
};
SQT_TABLE_BEGIN(EntityCustom, EntityCustom)
//Defines a column with a custom value source.
SQT_COLUMN_CUSTOM(CustomValue, CustomValueSource)
//Defines a column with an inline custom value source.
SQT_COLUMN_CUSTOM(InlineValue, struct ValueSource {
    using ValueType = std::string;
    static const std::string& GetValueFromEntity(const EntityCustom& entity) {
        return entity.value;
    }
    static void SetValueToEntity(EntityCustom& entity, std::string value) {
        entity.value = std::move(value);
    }
});
SQT_TABLE_END
}
SQT_REGISTER(value_source_test::EntityCustom)

TEST(ValueSourceTest, CustomValueSource) {

    using TableType = sqt::TableT<value_source_test::EntityCustom>;
    value_source_test::EntityCustom entity;
    entity.value = "value";

    //Custom value source
    {
        using ValueSource = typename TableType::CustomValueType::ValueSource;
        static_assert(sqt::ValueSourceType<ValueSource, value_source_test::EntityCustom>);

        const auto& value = ValueSource::GetValueFromEntity(entity);
        ASSERT_EQ(value, "value");

        ValueSource::SetValueToEntity(entity, "value2");
        ASSERT_EQ(entity.value, "value2");
    }

    //Inline value source
    {
        using ValueSource = typename TableType::InlineValueType::ValueSource;
        static_assert(sqt::ValueSourceType<ValueSource, value_source_test::EntityCustom>);

        const auto& value = ValueSource::GetValueFromEntity(entity);
        ASSERT_EQ(value, "value2");

        ValueSource::SetValueToEntity(entity, "value3");
        ASSERT_EQ(entity.value, "value3");
    }
}