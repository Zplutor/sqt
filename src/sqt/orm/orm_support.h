#pragma once

#include <array>
#include <sqt/orm/expression/expression_support.h>
#include <sqt/orm/internal/linked_list.h>
#include <sqt/orm/internal/primary_key_helper.h>
#include <sqt/orm/table_mapping.h>
#include <sqt/orm/table/abstract_index.h>
#include <sqt/orm/table/abstract_table.h>
#include <sqt/orm/table/column.h>
#include <sqt/orm/table/composite_column.h>
#include <sqt/orm/table/index_support.h>
#include <sqt/orm/table/primary_key_support.h>
#include <sqt/orm/utility/macro_utility.h>
#include <sqt/orm/utility/utility.h>
#include <sqt/orm/value/trivial_value_traits.h>

#define SQT_TABLE_BEGIN(TABLE_NAME, ENTITY_CLASS) \
namespace __sqt_table_##TABLE_NAME { \
using UserEntityType = ENTITY_CLASS; \
constexpr std::string_view UserTableName = #TABLE_NAME; \
class TableType : public sqt::AbstractTable { \
public: \
    using EntityType = UserEntityType; \
    static constexpr const TableType& GetInstance() noexcept; \
    static constexpr sqt::ColumnsView<EntityType> GetColumns() noexcept; \
    static constexpr sqt::ColumnsView<EntityType> GetPrimaryKeyColumns() noexcept; \
    static constexpr sqt::ColumnsView<EntityType> GetNonPrimaryKeyColumns() noexcept; \
    constexpr std::string_view GetName() const noexcept override { \
        return UserTableName; \
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


#define SQT_COLUMN(COLUMN_NAME, CLASS_FIELD) \
public: \
    class COLUMN_NAME##Type : public ColumnLinkedList::Node { \
    private: \
        using ThisType = COLUMN_NAME##Type; \
    public: \
        using ValueType = decltype(((EntityType*)nullptr)->CLASS_FIELD); \
        using ValueTraits = sqt::TrivialValueTraits<ValueType>; \
        using Node::Node; \
        static constexpr std::string_view Name = #COLUMN_NAME; \
        constexpr std::string_view GetName() const noexcept override { \
            return Name; \
        } \
        constexpr sqt::DataType GetDataType() const noexcept override { \
            return ValueTraits::DataType; \
        } \
        constexpr bool IsNullable() const noexcept override { \
            return ValueTraits::IsNullable; \
        } \
        void BindValueToStatement( \
            sqt::Statement& statement, \
            int parameter_index, \
            const EntityType& entity) const override { \
            ValueTraits::BindValueToStatement( \
                statement, parameter_index, entity.CLASS_FIELD); \
        } \
        void GetValueFromStatement( \
            const sqt::Statement& statement, \
            int column_index, \
            EntityType& entity) const override { \
            entity.CLASS_FIELD = ValueTraits::GetValueFromStatement(statement, column_index); \
        } \
        __SQT_EXPRESSION_OPERATORS(ThisType, ValueType) \
    }; \
    COLUMN_NAME##Type COLUMN_NAME{ column_linked_list_.Last() };


#define SQT_PRIMARY_KEY(...) SQT_DEFINE_PRIMARY_KEY(false, __VA_ARGS__)
#define SQT_PRIMARY_KEY_AUTO_INC(COLUMN_NAME) SQT_DEFINE_PRIMARY_KEY(true, COLUMN_NAME)


#define SQT_INDEX(...) SQT_DEFINE_INDEX(false, __VA_ARGS__)
#define SQT_INDEX_UNIQUE(...) SQT_DEFINE_INDEX(true, __VA_ARGS__)


#define SQT_TABLE_END \
    class Insider; \
}; \
class TableType::Insider { \
private: \
    template<std::size_t Count> \
    using ColumnArray = std::array<const sqt::Column<UserEntityType>*, Count>; \
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
constexpr sqt::ColumnsView<UserEntityType> TableType::GetColumns() noexcept { \
    return Insider::Columns; \
} \
constexpr sqt::ColumnsView<UserEntityType> TableType::GetPrimaryKeyColumns() noexcept { \
    return sqt::internal::PrimaryKeyShim<TableType>::GetPKColumns(Insider::TableInstance); \
} \
constexpr sqt::ColumnsView<UserEntityType> TableType::GetNonPrimaryKeyColumns() noexcept { \
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


#define SQT_REGISTER(NAMESPACE, TABLE_NAME) \
namespace sqt { \
template<> \
struct Table<NAMESPACE::__sqt_table_##TABLE_NAME::UserEntityType> { \
    using type = NAMESPACE::__sqt_table_##TABLE_NAME::TableType; \
}; \
}
