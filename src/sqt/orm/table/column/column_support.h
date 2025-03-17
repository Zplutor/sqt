#pragma once

#include <sqt/orm/value/trivial/basic/basic_value_traits_mapping.h>

#define __SQT_COLUMN_BEGIN(COLUMN_NAME) \
public: \
    class COLUMN_NAME##Type : public ColumnLinkedList::Node { \
    private: \
        using ThisType = COLUMN_NAME##Type; \
    public: \
        using Node::Node; \
        static constexpr std::string_view Name = #COLUMN_NAME; \
        constexpr std::string_view GetName() const noexcept override { \
            return Name; \
        }


#define __SQT_VALUE_SOURCE_FIELD(FIELD) \
        class ValueSource { \
        public: \
            using ValueType = decltype(((UserEntityType*)nullptr)->FIELD); \
            static const ValueType& GetValueFromEntity(const EntityType& entity) { \
                return entity.FIELD; \
            } \
            static void SetValueToEntity(EntityType& entity, ValueType&& value) { \
                entity.FIELD = std::move(value); \
            } \
        };


#define __SQT_COLUMN_END(COLUMN_NAME) \
        using ValueType = typename ValueSource::ValueType; \
        using ValueTraits = sqt::BasicValueTraitsForT<ValueType>; \
        static void BindValueFromEntity( \
            sqt::Statement& statement, \
            int parameter_index, \
            const EntityType& entity) { \
            const auto& value = ValueSource::GetValueFromEntity(entity); \
            ValueTraits::BindValue(statement, parameter_index, value); \
        } \
        static void RetrieveValueToEntity( \
            const sqt::Statement& statement, \
            int column_index, \
            EntityType& entity) { \
            auto value = ValueTraits::RetrieveValue(statement, column_index); \
            ValueSource::SetValueToEntity(entity, std::move(value)); \
        } \
        constexpr sqt::DataType GetDataType() const noexcept override { \
            return ValueTraits::DataType; \
        } \
        constexpr bool IsNullable() const noexcept override { \
            return ValueTraits::IsNullable; \
        } \
        void VirtualBindValueFromEntity( \
            sqt::Statement& statement, \
            int parameter_index, \
            const EntityType& entity) const override { \
            BindValueFromEntity(statement, parameter_index, entity); \
        } \
        void VirtualRetrieveValueToEntity( \
            const sqt::Statement& statement, \
            int column_index, \
            EntityType& entity) const override { \
            RetrieveValueToEntity(statement, column_index, entity); \
        } \
        __SQT_EXPRESSION_OPERATORS(ThisType) \
    }; \
    COLUMN_NAME##Type COLUMN_NAME{ column_linked_list_.Last() };