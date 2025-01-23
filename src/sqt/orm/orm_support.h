#pragma once

#include <array>
#include <sqt/orm/column/column.h>
#include <sqt/orm/column/composite_column.h>
#include <sqt/orm/expression/expression_support.h>
#include <sqt/orm/index/abstract_index.h>
#include <sqt/orm/index/index_support.h>
#include <sqt/orm/internal/linked_list.h>
#include <sqt/orm/table_mapping.h>
#include <sqt/orm/table/abstract_table.h>
#include <sqt/orm/utility/macro_utility.h>
#include <sqt/orm/value_type/primitive_value_type.h>
#include <sqt/orm/value_type/nullable_value_type.h>

#define SQT_TABLE_BEGIN(TABLE_NAME, ENTITY_CLASS) \
namespace __sqt_table_##TABLE_NAME { \
using EntityType = ENTITY_CLASS; \
class TableType : public sqt::AbstractTable { \
public: \
    static constexpr const TableType& GetInstance() noexcept; \
    constexpr std::string_view GetName() const noexcept override { \
        return #TABLE_NAME; \
    } \
    constexpr sqt::ColumnsView<EntityType> GetColumns() const noexcept; \
    sqt::AbstractColumnsView GetAbstractColumns() const noexcept override; \
    sqt::AbstractIndexesView GetAbstractIndexes() const noexcept override; \
private: \
    constexpr TableType() noexcept = default; \
    using ColumnLinkedList = sqt::LinkedList<sqt::Column<EntityType>>; \
    ColumnLinkedList column_linked_list_; \
    using IndexLinkedList = sqt::LinkedList<sqt::AbstractIndex>; \
    IndexLinkedList index_linked_list_; \
    template<typename... Columns> \
    class BaseIndex : public sqt::CompositeColumn<Columns...>, public IndexLinkedList::Node { \
    public: \
        constexpr BaseIndex( \
            const IndexLinkedList::Node*& last_index, \
            const Columns&... columns) : \
            sqt::CompositeColumn<Columns...>(columns...), \
            IndexLinkedList::Node(last_index) { } \
        sqt::AbstractColumnsView GetAbstractColumns() const noexcept override { \
            return sqt::CompositeColumn<Columns...>::GetAbstractColumns(); \
        } \
    }; \
    template<typename... Columns> \
    static constexpr BaseIndex<Columns...> MakeBaseIndex(const Columns&...) { } \


#define SQT_COLUMN(COLUMN_NAME, CLASS_FIELD) \
public: \
    class COLUMN_NAME##Type : public ColumnLinkedList::Node { \
    private: \
        using ThisType = COLUMN_NAME##Type; \
    public: \
        using ValueType = decltype(((EntityType*)nullptr)->CLASS_FIELD); \
        using ValueTypeTraits = sqt::ValueTypeTraits<ValueType>; \
        using Node::Node; \
        constexpr std::string_view GetName() const noexcept override { \
            return #COLUMN_NAME; \
        } \
        constexpr sqt::DataType GetDataType() const noexcept override { \
            return ValueTypeTraits::DataType; \
        } \
        constexpr bool IsNullable() const noexcept override { \
            return ValueTypeTraits::IsNullable; \
        } \
        void BindValueToStatement( \
            sqt::Statement& statement, \
            int parameter_index, \
            const EntityType& entity) const override { \
        } \
        void GetValueFromStatement( \
            const sqt::Statement& statement, \
            int column_index, \
            EntityType& entity) const override { \
        } \
        __SQT_EXPRESSION_OPERATORS(ThisType, ValueType) \
    }; \
    COLUMN_NAME##Type COLUMN_NAME{ column_linked_list_.Last() };


#define SQT_INDEX(...) \
private: \
    using SQT_INDEX_BASE_TYPE_NAME(__VA_ARGS__) = decltype(MakeBaseIndex(__VA_ARGS__)); \
public: \
    class SQT_INDEX_TYPE_NAME(__VA_ARGS__) : public SQT_INDEX_BASE_TYPE_NAME(__VA_ARGS__) { \
    public: \
        using SQT_INDEX_BASE_TYPE_NAME(__VA_ARGS__)::SQT_INDEX_BASE_TYPE_NAME(__VA_ARGS__); \
    }; \
    SQT_INDEX_TYPE_NAME(__VA_ARGS__) SQT_INDEX_NAME(__VA_ARGS__){ \
        index_linked_list_.Last(), __VA_ARGS__ };


#define SQT_TABLE_END \
    class Insider; \
}; \
class TableType::Insider { \
public: \
    static constexpr TableType TableInstance; \
    static constexpr std::size_t ColumnCount = TableInstance.column_linked_list_.Count(); \
    static constexpr std::array<const sqt::Column<EntityType>*, ColumnCount> Columns = \
        TableInstance.column_linked_list_.ToNodeBaseArray<ColumnCount>(); \
    static constexpr std::size_t IndexCount = TableInstance.index_linked_list_.Count(); \
    static constexpr std::array<const sqt::AbstractIndex*, IndexCount> Indexes = \
        TableInstance.index_linked_list_.ToNodeBaseArray<IndexCount>(); \
}; \
constexpr const TableType& TableType::GetInstance() noexcept { \
    return Insider::TableInstance; \
} \
constexpr sqt::ColumnsView<EntityType> TableType::GetColumns() const noexcept { \
    return TableType::Insider::Columns; \
} \
inline sqt::AbstractColumnsView TableType::GetAbstractColumns() const noexcept { \
    return { \
        reinterpret_cast<const sqt::AbstractColumn* const*>(GetColumns().data()), \
        GetColumns().size() \
    }; \
} \
inline sqt::AbstractIndexesView TableType::GetAbstractIndexes() const noexcept { \
    return TableType::Insider::Indexes; \
} \
};


#define SQT_REGISTER(NAMESPACE, TABLE_NAME) \
namespace sqt { \
template<> \
struct Table<NAMESPACE::__sqt_table_##TABLE_NAME::EntityType> { \
    using type = NAMESPACE::__sqt_table_##TABLE_NAME::TableType; \
}; \
}