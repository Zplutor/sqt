#pragma once

#include <array>
#include <sqt/orm/table/definition/expression_definition.h>
#include <sqt/orm/internal/linked_list.h>
#include <sqt/orm/internal/primary_key_helper.h>
#include <sqt/orm/table_mapping.h>
#include <sqt/orm/table/index/abstract_index.h>
#include <sqt/orm/table/abstract_table.h>
#include <sqt/orm/table/column/column.h>
#include <sqt/orm/table/definition/column_definition.h>
#include <sqt/orm/table/column/composite_column.h>
#include <sqt/orm/table/definition/index_definition.h>
#include <sqt/orm/table/definition/primary_key_definition.h>
#include <sqt/orm/utility/macro_utility.h>
#include <sqt/orm/utility/utility.h>

#define SQT_TABLE_BEGIN(TABLE_NAME, ENTITY_CLASS) \
namespace TABLE_NAME##_definition { \
using TableEntityType = ENTITY_CLASS; \
constexpr std::string_view TableName = #TABLE_NAME; \
class TableType : public sqt::AbstractTable { \
public: \
    using EntityType = TableEntityType; \
    static constexpr const TableType& GetInstance() noexcept; \
    static constexpr sqt::ColumnsView<EntityType> GetColumns() noexcept; \
    static constexpr sqt::ColumnsView<EntityType> GetPrimaryKeyColumns() noexcept; \
    static constexpr sqt::ColumnsView<EntityType> GetNonPrimaryKeyColumns() noexcept; \
    constexpr std::string_view GetName() const noexcept override { \
        return TableName; \
    } \
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


#define SQT_COLUMN_FIELD(COLUMN_NAME, CLASS_FIELD) \
__SQT_COLUMN_BEGIN(COLUMN_NAME) \
__SQT_VALUE_SOURCE_FIELD(CLASS_FIELD) \
__SQT_COLUMN_END(COLUMN_NAME)


#define SQT_COLUMN_ACCESSOR(COLUMN_NAME, GETTER, SETTER) \
__SQT_COLUMN_BEGIN(COLUMN_NAME) \
__SQT_VALUE_SOURCE_ACCESSOR(GETTER, SETTER) \
__SQT_COLUMN_END(COLUMN_NAME)


#define SQT_COLUMN_CUSTOM(COLUMN_NAME, VALUE_SOURCE) \
__SQT_COLUMN_BEGIN(COLUMN_NAME) \
__SQT_VALUE_SOURCE_CUSTOM(VALUE_SOURCE) \
__SQT_COLUMN_END(COLUMN_NAME)


#define SQT_PRIMARY_KEY(...) __SQT_PRIMARY_KEY(false, __VA_ARGS__)
#define SQT_PRIMARY_KEY_AUTO_INC(COLUMN_NAME) __SQT_PRIMARY_KEY(true, COLUMN_NAME)


#define SQT_INDEX(...) __SQT_INDEX(false, __VA_ARGS__)
#define SQT_INDEX_UNIQUE(...) __SQT_INDEX(true, __VA_ARGS__)


#define SQT_TABLE_END \
    class Insider; \
}; \
class TableType::Insider { \
private: \
    template<std::size_t Count> \
    using ColumnArray = std::array<const sqt::Column<TableEntityType>*, Count>; \
    using PKShim = sqt::internal::PrimaryKeyShim<TableType>; \
    using PKHelper = sqt::internal::PrimaryKeyHelper<TableType>; \
public: \
    static constexpr TableType TableInstance; \
    static constexpr std::size_t ColumnCount = TableInstance.column_linked_list_.Count(); \
    static constexpr ColumnArray<ColumnCount> Columns = \
        TableInstance.column_linked_list_.ToNodeBaseArray<ColumnCount>(); \
    static constexpr std::size_t PKColumnCount = PKShim::PKColumnCount; \
    static constexpr std::size_t NonPKColumnCount = ColumnCount - PKColumnCount; \
    static constexpr ColumnArray<NonPKColumnCount> NonPKColumns = \
        PKHelper::MakeNonPKColumns<TableType::ColumnLinkedList, NonPKColumnCount>( \
            TableInstance.column_linked_list_, PKShim::GetPKColumnIndexes(TableInstance)); \
    static constexpr std::size_t IndexCount = TableInstance.index_linked_list_.Count(); \
    static constexpr std::array<const sqt::AbstractIndex*, IndexCount> Indexes = \
        TableInstance.index_linked_list_.ToNodeBaseArray<IndexCount>(); \
}; \
constexpr const TableType& TableType::GetInstance() noexcept { \
    return Insider::TableInstance; \
} \
constexpr sqt::ColumnsView<TableEntityType> TableType::GetColumns() noexcept { \
    return Insider::Columns; \
} \
constexpr sqt::ColumnsView<TableEntityType> TableType::GetPrimaryKeyColumns() noexcept { \
    return sqt::internal::PrimaryKeyShim<TableType>::GetPKColumns(Insider::TableInstance); \
} \
constexpr sqt::ColumnsView<TableEntityType> TableType::GetNonPrimaryKeyColumns() noexcept { \
    return Insider::NonPKColumns; \
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


#define SQT_REGISTER(QUALIFIED_TABLE_NAME) \
namespace sqt { \
template<> \
struct TableMapping<QUALIFIED_TABLE_NAME##_definition::TableEntityType> { \
    using type = QUALIFIED_TABLE_NAME##_definition::TableType; \
}; \
}
