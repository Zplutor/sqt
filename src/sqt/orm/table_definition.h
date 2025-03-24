#pragma once

/**
@file
    Defines macros for defining table types for entities types.
*/

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

/**
Begins the definition of a table type for the specified entity type.

@tparam TABLE_NAME
    The name of the table. It will be the table name in the database.

@tparam ENTITY_TYPE
    The entity type for which the table type is being defined. If this macro is used in a different
    namespace from the entity type, the namespace must be explicitly specified.

@details
    This macro opens the definition of a table type, which must be closed using the `SQT_TABLE_END`
    macro. Within the definition, the following macros can be used:

    - Defining columns:
        - `SQT_COLUMN_FIELD`
        - `SQT_COLUMN_ACCESSOR`
        - `SQT_COLUMN_CUSTOM`
    - Defining primary key:
        - `SQT_PRIMARY_KEY`
        - `SQT_PRIMARY_KEY_AUTO_INC`
    - Defining indexes:
        - `SQT_INDEX`
        - `SQT_INDEX_UNIQUE`

    This macro can be used in any namespace. If the entity type is defined in a different 
    namespace, `ENTITY_TYPE` must be prefixed with its namespace to ensure proper resolution.
    
    While identical table names can exist in different namespaces, this is discouraged as it may
    cause name conflicts when used within the same database.

    Example usage:
    @code
    namespace my_scope {

    class MyEntity { };

    //Define the table type in the same namespace as the entity type.
    SQT_TABLE_BEGIN(MyEntityTable1, MyEntity)
    SQT_TABLE_END

    }

    //Define the table type in the different namespace from the entity type.
    SQT_TABLE_BEGIN(MyEntityTable2, my_scope::MyEntity)
    SQT_TABLE_END
    @endcode

    After defining a table type, it must be registered in the framework using the `SQT_REGISTER`
    macro. After registration, the helper templates `sqt::TableType<>` and `sqt::Table<>` allow 
    access to the table type and its singleton instance.

    The following class demonstrates the expected interface of a defined table type:
    @code
    class TableType : public sqt::AbstractTable {
    public:
        //Type alias for the associated entity type.
        using EntityType = ENTITY_TYPE;

        //Retrieves the singleton instance of the table type.
        static constexpr const TableType& GetInstance() noexcept;

        //Retrieves all columns of the table.
        static constexpr sqt::ColumnsView<EntityType> GetColumns() noexcept; 

        //Retrieves the columns that form the primary key.
        //If no primary key is defined, an empty view is returned.
        static constexpr sqt::ColumnsView<EntityType> GetPrimaryKeyColumns() noexcept; 

        //Retrieves the columns that are not part of the primary key.
        //If no primary key is defined, this is equivalent to GetColumns().
        static constexpr sqt::ColumnsView<EntityType> GetNonPrimaryKeyColumns() noexcept;

        //Forbids copying.
        TableType(const TableType&) = delete;
        TableType& operator=(const TableType&) = delete;

        //Forbids moving.
        TableType(TableType&&) = delete;
        TableType& operator=(TableType&&) = delete;

    private:
        constexpr TableType() noexcept;
    };
    @endcode
    
@see SQT_COLUMN_FIELD
@see SQT_COLUMN_ACCESSOR
@see SQT_COLUMN_CUSTOM
@see SQT_PRIMARY_KEY
@see SQT_PRIMARY_KEY_AUTO_INC
@see SQT_INDEX
@see SQT_INDEX_UNIQUE
@see SQT_TABLE_END
@see SQT_REGISTER
@see sqt::TableType<>
@see sqt::Table<>
*/
#define SQT_TABLE_BEGIN(TABLE_NAME, ENTITY_TYPE) \
namespace TABLE_NAME##_definition { \
using TableEntityType = ENTITY_TYPE; \
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


/**
Registers the specified table type in the framework, enabling ORM capabilities for the associated
entity type.

@param QUALIFIED_TABLE_NAME
    The fully qualified table name, including its namespace, where it is defined using 
    `SQT_TABLE_BEGIN`.

@details
    This macro generates a partial specialization of the `sqt::TableMapping` primary template, 
    mapping the entity type to its corresponding table type.

    @note
        This macro must be used in the global scope.

    Example usage:
    @code
    namespace my_scope {

    class MyEntity { };

    //Define the table type for the entity type.
    SQT_TABLE_BEGIN(MyEntityTable, MyEntity)
    SQT_TABLE_END

    }

    //Register the table type in the framework.
    SQT_REGISTER(my_scope::MyEntityTable)
    @endcode

@see `SQT_TABLE_BEGIN`
@see `sqt::TableMapping<>`
*/
#define SQT_REGISTER(QUALIFIED_TABLE_NAME) \
namespace sqt { \
template<> \
struct TableMapping<QUALIFIED_TABLE_NAME##_definition::TableEntityType> { \
    using type = QUALIFIED_TABLE_NAME##_definition::TableType; \
}; \
}
