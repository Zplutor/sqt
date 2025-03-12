#pragma once

#include <sqt/orm/table/column/default_column_descriptor.h>

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


#define __SQT_COLUMN_DESCRIPTOR_FIELD(FIELD) \
        using ValueType = decltype(((UserEntityType*)nullptr)->FIELD); \
        class Descriptor : public sqt::DefaultColumnDescriptor<ValueType> { \
        public: \
            using EntityType = UserEntityType; \
            static const ValueType& GetValueFromEntity(const EntityType& entity) {\
                return entity.FIELD; \
            } \
            static void SetValueToEntity(EntityType& entity, ValueType&& value) {\
                entity.FIELD = std::move(value); \
            } \
        }; \


#define __SQT_COLUMN_END(COLUMN_NAME) \
        using ValueTraits = typename Descriptor::ValueTraits; \
        static void BindValueFromEntity( \
            sqt::Statement& statement, \
            int parameter_index, \
            const EntityType& entity) { \
            const auto& value = Descriptor::GetValueFromEntity(entity); \
            ValueTraits::BindValue(statement, parameter_index, value); \
        } \
        static void RetrieveValueToEntity( \
            const sqt::Statement& statement, \
            int column_index, \
            EntityType& entity) { \
            auto value = ValueTraits::RetrieveValue(statement, column_index); \
            Descriptor::SetValueToEntity(entity, std::move(value)); \
        } \
        constexpr sqt::DataType GetDataType() const noexcept override { \
            return Descriptor::DataType; \
        } \
        constexpr bool IsNullable() const noexcept override { \
            return Descriptor::IsNullable; \
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