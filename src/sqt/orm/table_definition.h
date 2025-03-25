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

    // Define the table type in the same namespace as the entity type.
    SQT_TABLE_BEGIN(MyEntityTable1, MyEntity)
    SQT_TABLE_END

    }

    // Define the table type in the different namespace from the entity type.
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
        // Type alias for the associated entity type.
        using EntityType = ENTITY_TYPE;

        // Retrieves the singleton instance of the table type.
        static constexpr const TableType& GetInstance() noexcept;

        // Retrieves all columns of the table.
        static constexpr sqt::ColumnsView<EntityType> GetColumns() noexcept; 

        // Retrieves the columns that form the primary key.
        // If no primary key is defined, an empty view is returned.
        static constexpr sqt::ColumnsView<EntityType> GetPrimaryKeyColumns() noexcept; 

        // Retrieves the columns that are not part of the primary key.
        // If no primary key is defined, this is equivalent to GetColumns().
        static constexpr sqt::ColumnsView<EntityType> GetNonPrimaryKeyColumns() noexcept;

        // Forbids copying.
        TableType(const TableType&) = delete;
        TableType& operator=(const TableType&) = delete;

        // Forbids moving.
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
@see sqt::AbstractTable
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


/**
Defines a column that binds to the specified field of the entity type.

@param COLUMN_NAME
    The name of the column. It will be the column name in the database.

@param FIELD
    The field of the entity type to which the column is bound.

@details
    This macro must be used between the `SQT_TABLE_BEGIN` and `SQT_TABLE_END` macros.

    Each column name must be unique within a table definition to avoid conflicts.

    A field is a public member variable of the entity type. The framework reads from and writes to 
    the field when performing mapping between entity instances and database rows. The type of the
    field must satisify the requirements of the `sqt::BasicValueType` concept.

    Example usage:
    @code
    struct MyEntity {
        int id{};
        std::string name;
    };

    SQT_TABLE_BEGIN(MyEntityTable, MyEntity)
    SQT_COLUMN_FIELD(ID, id)
    SQT_COLUMN_FIELD(Name, name)
    SQT_TABLE_END
    @endcode

    The following code demonstrates the generated definition of the `ID` column in the table type:
    @code
    class TableType {
    public:
        using EntityType = ENTITY_TYPE;

        // The class name of the column type is generated by appending "Type" to the column name.
        class IDType : public sqt::Column<EntityType> {
        public:
            // The name of the column.
            static constexpr std::string_view Name = "ID";

            // The value source type determines the column's value type and provides methods for 
            // reading from and writing to an entity instance
            class ValueSource;

            // The value type of the column, which is obtained from the ValueSource.
            using ValueType = int;

            // The value traits type that defines how the value is bound to and retrieved from the 
            // database statement.
            using ValueTraits = sqt::BasicValueTraitsForT<ValueType>;

            // Forbids copying.
            IDType(const IDType&) = delete;
            IDType& operator=(const IDType&) = delete;

            // Forbids moving.
            IDType(IDType&&) = delete;
            IDType& operator=(IDType&&) = delete;

            // Assignment operator that generates an assignment expression which can be used in
            // set clauses.
            constexpr auto operator=(const ValueType&) const noexcept;

            // Ordering operator that generates an ordering term expression which can be used in
            // order by clauses.
            constexpr auto Asc() const noexcept;
            constexpr auto Desc() const noexcept;

            // Comparison operators that generate predicate expressions which can be used in 
            // where clauses.
            friend constexpr auto operator==(const IDType&, const ValueType&) const noexcept;
            friend constexpr auto operator!=(const IDType&, const ValueType&) const noexcept;
            friend constexpr auto operator<(const IDType&, const ValueType&) const noexcept;
            friend constexpr auto operator<=(const IDType&, const ValueType&) const noexcept;
            friend constexpr auto operator>(const IDType&, const ValueType&) const noexcept;
            friend constexpr auto operator>=(const IDType&, const ValueType&) const noexcept;

            friend constexpr auto operator==(const IDType&, sqt::Placeholder) const noexcept;
            friend constexpr auto operator!=(const IDType&, sqt::Placeholder) const noexcept;
            friend constexpr auto operator<(const IDType&, sqt::Placeholder) const noexcept;
            friend constexpr auto operator<=(const IDType&, sqt::Placeholder) const noexcept;
            friend constexpr auto operator>(const IDType&, sqt::Placeholder) const noexcept;
            friend constexpr auto operator>=(const IDType&, sqt::Placeholder) const noexcept;

            friend constexpr auto operator==(const ValueType&, const IDType&) const noexcept;
            friend constexpr auto operator!=(const ValueType&, const IDType&) const noexcept;
            friend constexpr auto operator<(const ValueType&, const IDType&) const noexcept;
            friend constexpr auto operator<=(const ValueType&, const IDType&) const noexcept;
            friend constexpr auto operator>(const ValueType&, const IDType&) const noexcept;
            friend constexpr auto operator>=(const ValueType&, const IDType&) const noexcept;

            friend constexpr auto operator==(sqt::Placeholder, const IDType&) const noexcept;
            friend constexpr auto operator!=(sqt::Placeholder, const IDType&) const noexcept;
            friend constexpr auto operator<(sqt::Placeholder, const IDType&) const noexcept;
            friend constexpr auto operator<=(sqt::Placeholder, const IDType&) const noexcept;
            friend constexpr auto operator>(sqt::Placeholder, const IDType&) const noexcept;
            friend constexpr auto operator>=(sqt::Placeholder, const IDType&) const noexcept;
        };

        // The instance of the column, which is defined as a public member variable of the table 
        // type. The name of the variable is the same as the column name.
        IDType ID;
    };
    @endcode

    To define a column that binds to a pair of accessor methods, use the `SQT_COLUMN_ACCESSOR` 
    macro. To define a column that binds to a custom value source, use the `SQT_COLUMN_CUSTOM` 
    macro.

@see SQT_TABLE_BEGIN
@see SQT_TABLE_END
@see SQT_COLUMN_ACCESSOR
@see SQT_COLUMN_CUSTOM
@see sqt::BasicValueType
@see sqt::Column<>
*/
#define SQT_COLUMN_FIELD(COLUMN_NAME, FIELD) \
__SQT_COLUMN_BEGIN(COLUMN_NAME) \
__SQT_VALUE_SOURCE_FIELD(FIELD) \
__SQT_COLUMN_END(COLUMN_NAME)


/**
Defines a column that binds to the specified accessor methods of the entity type.

@param COLUMN_NAME
    The name of the column. It will be the column name in the database.

@param GETTER
    A const member function of the entity type that retrieves the column value from an entity 
    instance.

@param SETTER
    A non-const member function of the entity type that assigns the column value to an entity 
    instance.

@details
    This macro is similar to `SQT_COLUMN_FIELD`, except that it binds to a pair of accessor methods
    instead of a public member variable.

    The getter method must be a const member function that takes no arguments and returns a value.
    The return type must satisfy the requirements of the `sqt::BasicValueType` concept. The 
    column's value type is deduced from this return type.
    
    The setter method must be a non-const member function that accepts a value convertible from the
    getter's return type as its parameter.

    Example usage:
    @code
    class MyEntity {
    public:
        int GetID() const {
            return id_;
        }

        void SetID(int id) {
            id_ = id;
        }

        const std::string& GetName() const {
            return name_;
        }

        void SetName(std::string_view name) {
            name_ = std::string{ name };
        }

    private:
        int id_{};
        std::string name_;
    };

    SQT_TABLE_BEGIN(MyEntityTable, MyEntity)
    SQT_COLUMN_ACCESSOR(ID, GetID, SetID)
    SQT_COLUMN_ACCESSOR(Name, GetName, SetName)
    SQT_TABLE_END
    @endcode
   
@see SQT_COLUMN_FIELD
*/
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


/**
Ends the definition of a table type.

@details
    This macro closes the definition of a table type that was opened using the `SQT_TABLE_BEGIN` 
    macro.

@see SQT_TABLE_BEGIN
*/
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

    // Define the table type for the entity type.
    SQT_TABLE_BEGIN(MyEntityTable, MyEntity)
    SQT_TABLE_END

    }

    // Register the table type in the framework.
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
