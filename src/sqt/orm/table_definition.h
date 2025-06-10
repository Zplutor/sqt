#pragma once

/**
@file
    Defines macros for defining table types for entities types.
*/

#include <array>
#include <sqt/orm/table/definition/expression_definition.h>
#include <sqt/orm/internal/linked_list.h>
#include <sqt/orm/internal/macro_utility.h>
#include <sqt/orm/internal/primary_key_helper.h>
#include <sqt/orm/internal/utility.h>
#include <sqt/orm/table_mapping.h>
#include <sqt/orm/table/index/abstract_index.h>
#include <sqt/orm/table/abstract_table.h>
#include <sqt/orm/table/column/column.h>
#include <sqt/orm/table/definition/column_definition.h>
#include <sqt/orm/table/column/composite_column.h>
#include <sqt/orm/table/definition/index_definition.h>
#include <sqt/orm/table/definition/primary_key_definition.h>

/**
Begins the definition of a table type for the specified entity type.

@param TABLE_NAME
    The name of the table. It will be the table name in the database.

@param ENTITY_TYPE
    The entity type for which the table type is being defined. If this macro is used in a different
    namespace from the entity type, the namespace must be explicitly specified.

@details
    This macro opens the definition of a table type, which must be closed using the `SQT_TABLE_END`
    macro. Within the definition, the following macros can be used:

    - Defining columns:
        - `SQT_COLUMN_FIELD`
        - `SQT_COLUMN_FIELD_2`
        - `SQT_COLUMN_ACCESSOR`
        - `SQT_COLUMN_ACCESSOR_2`
        - `SQT_COLUMN_CUSTOM`
        - `SQT_COLUMN_CUSTOM_2`
    - Defining primary key:
        - `SQT_PRIMARY_KEY`
        - `SQT_PRIMARY_KEY_AUTO_INC`
    - Defining indexes:
        - `SQT_INDEX`
        - `SQT_INDEX_UNIQUE`
        - `SQT_INDEX_NAMED`
        - `SQT_INDEX_NAMED_UNIQUE`

    This macro can be used in any namespace, including the anonymous namespace. If the entity type 
    is defined in a different namespace, `ENTITY_TYPE` must be prefixed with its namespace to 
    ensure proper resolution.
    
    @note
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

    The following class demonstrates the expected interface of a defined table type:
    @code
    class TableType : public sqt::AbstractTable {
    public:
        // Type alias for the associated entity type.
        using EntityType = ENTITY_TYPE;

        // Retrieves the singleton instance of the table type.
        static constexpr const TableType& GetInstance() noexcept;

        // Retrieves all columns of the table.
        constexpr sqt::ColumnsView<EntityType> GetColumns() const noexcept; 

        // Retrieves the columns that form the primary key.
        // If no primary key is defined, an empty view is returned.
        constexpr sqt::ColumnsView<EntityType> GetPrimaryKeyColumns() const noexcept; 

        // Retrieves the columns that are not part of the primary key.
        // If no primary key is defined, this is equivalent to GetColumns().
        constexpr sqt::ColumnsView<EntityType> GetNonPrimaryKeyColumns() const noexcept;

        // Retrieves the column of the specified column type.
        template<sqt::ColumnType COLUMN>
        constexpr const sqt::Column<EntityType>* GetColumn() const noexcept;

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

    @note
    After defining a table type, it must be registered in the framework using the `SQT_REGISTER`
    macro.

    After registration, the helper templates `sqt::TableType<>` and `sqt::Table<>` allow
    access to the table type and its singleton instance.

    @note
    While it is legal to define multiple table types for the same entity type, only one table type 
    can be registered for each entity type. Attempting to register multiple table types for the 
    same entity type will result in a compilation error.
    
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
    constexpr sqt::ColumnsView<EntityType> GetColumns() const noexcept; \
    constexpr sqt::ColumnsView<EntityType> GetPrimaryKeyColumns() const noexcept; \
    constexpr sqt::ColumnsView<EntityType> GetNonPrimaryKeyColumns() const noexcept; \
    constexpr std::string_view GetName() const noexcept override { \
        return TableName; \
    } \
    sqt::AbstractColumnsView GetAbstractColumns() const noexcept override; \
    sqt::AbstractIndexesView GetAbstractIndexes() const noexcept override; \
    template<sqt::ColumnType COLUMN> \
    constexpr const sqt::Column<EntityType>* GetColumn() const noexcept { \
        static_assert(false, "The column type is not defined for this table."); \
    } \
private: \
    constexpr TableType() noexcept = default; \
    using ColumnLinkedList = sqt::LinkedList<sqt::Column<EntityType>>; \
    ColumnLinkedList column_linked_list_; \
    using IndexLinkedList = sqt::LinkedList<sqt::AbstractIndex>; \
    IndexLinkedList index_linked_list_;


/**
Defines a column that binds to the specified field of the entity type.

@param COLUMN_NAME
    The name of the column in the database. It will be also used as the instance name of the 
    column.

@param FIELD
    The field of the entity type to which the column is bound.

@details
    This macro must be used between the `SQT_TABLE_BEGIN` and `SQT_TABLE_END` macros.

    Each column name must be unique within a table definition to avoid conflicts.

    A field is a public member variable of the entity type. The framework reads from and writes to 
    the field when performing mapping between entity instances and database rows. The type of the
    field must satisfy the requirements of the `sqt::BasicValueType` concept.

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

        // The class name of the column type is generated by appending the column name to 
        // "ColumnType_".
        class ColumnType_ID : public sqt::Column<EntityType> {
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
            using ValueTraits = sqt::BasicValueTraitsMappingT<ValueType>;

            // Forbids copying.
            IDType(const IDType&) = delete;
            IDType& operator=(const IDType&) = delete;

            // Forbids moving.
            IDType(IDType&&) = delete;
            IDType& operator=(IDType&&) = delete;

            // Assignment operator that generates an assignment expression.
            constexpr auto operator=(const ValueType&) const noexcept;

            // Ordering operator that generates an ordering term expression.
            constexpr auto Asc() const noexcept;
            constexpr auto Desc() const noexcept;

            // Comparison operators that generate predicate expressions.
            // Here shows only the == operator. Other operators (!=, <, <=, >, >=) are omitted.
            friend constexpr auto operator==(const IDType&, const ValueType&) const noexcept;
            friend constexpr auto operator==(const IDType&, sqt::Placeholder) const noexcept;
            friend constexpr auto operator==(const ValueType&, const IDType&) const noexcept;
            friend constexpr auto operator==(sqt::Placeholder, const IDType&) const noexcept;
        };

        // The instance of the column, which is defined as a public member variable of the table 
        // type. The name of the variable is the same as the column name.
        ColumnType_ID ID;
    };
    @endcode

    The class name and the instance name of the column is auto-generated from the used-defined 
    column name, this may cause name collision with other names generated by the framework. To 
    resolve the collision, use the `SQT_COLUMN_FIELD_2` overload macro to provide a custom instance
    name of the column.

    To define a column that binds to a pair of accessor methods, use the `SQT_COLUMN_ACCESSOR` or
    SQT_COLUMN_ACCESSOR_2` macros. To define a column that binds to a custom value source, use the 
    `SQT_COLUMN_CUSTOM` or `SQT_COLUMN_CUSTOM_2` macros.

@see SQT_TABLE_BEGIN
@see SQT_TABLE_END
@see SQT_COLUMN_ACCESSOR
@see SQT_COLUMN_ACCESSOR_2
@see SQT_COLUMN_CUSTOM
@see SQT_COLUMN_CUSTOM_2
@see SQT_COLUMN_FIELD_2
@see sqt::BasicValueType
@see sqt::Column<>
*/
#define SQT_COLUMN_FIELD(COLUMN_NAME, FIELD) \
__SQT_COLUMN_BEGIN(COLUMN_NAME, COLUMN_NAME) \
__SQT_VALUE_SOURCE_FIELD(FIELD) \
__SQT_COLUMN_END(COLUMN_NAME, COLUMN_NAME)


/**
Defines a column with a custom instance name that binds to the specified field of the entity type.

@param COLUMN_NAME
    The name of the column in the database.

@param INSTANCE_NAME
    The name of the column instance.

@param FIELD
    The field of the entity type to which the column is bound.

@details
    This macro is similar to the `SQT_COLUMN_FIELD` macro, except that it allows specifying a 
    custom name for the column instance. This is useful in scenarios where the auto-generated 
    instance name would conflict with other names generated by the framework.
    
    The instance name is also used to generate the class name of the column type, which is
    formed by appending the instance name to the prefix `ColumnType_`.

    Example usage:
    @code{.cpp}
    struct MyEntity {
        int value{};
    };

    SQT_TABLE_BEGIN(MyEntityTable, MyEntity)
    SQT_COLUMN_FIELD_2(Value, CustomValue, value)
    SQT_TABLE_END
    @endcode

    The following code demonstrates the generated definition of the `Value` column in the table 
    type:
    @code{.cpp}
    class TableType {
    public:
        // The class name of the column type is generated by appending the instance name to
        // "ColumnType_".
        class ColumnType_CustomValue {
        public:
            // The column name in the database.
            static constexpr std::string_view Name = "ID";

            // Other definitions are omitted.
        };

        // The instance of the column.
        ColumnType_CustomValue CustomValue;
    };
    @endcode

@see SQT_COLUMN_FIELD
*/
#define SQT_COLUMN_FIELD_2(COLUMN_NAME, INSTANCE_NAME, FIELD) \
__SQT_COLUMN_BEGIN(COLUMN_NAME, INSTANCE_NAME) \
__SQT_VALUE_SOURCE_FIELD(FIELD) \
__SQT_COLUMN_END(COLUMN_NAME, INSTANCE_NAME)


/**
Defines a column that binds to the specified accessor methods of the entity type.

@param COLUMN_NAME
    The name of the column in the database. It will be also used as the instance name of the 
    column.

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
   
@see SQT_COLUMN_ACCESSOR_2
@see SQT_COLUMN_FIELD
*/
#define SQT_COLUMN_ACCESSOR(COLUMN_NAME, GETTER, SETTER) \
__SQT_COLUMN_BEGIN(COLUMN_NAME, COLUMN_NAME) \
__SQT_VALUE_SOURCE_ACCESSOR(GETTER, SETTER) \
__SQT_COLUMN_END(COLUMN_NAME, COLUMN_NAME)


/**
Defines a column with a custom instance name that binds to the specified accessor methods of the 
entity type.

@param COLUMN_NAME
    The name of the column in the database.

@param INSTANCE_NAME
    The name of the column instance.

@param GETTER
    A const member function of the entity type that retrieves the column value from an entity
    instance.

@param SETTER
    A non-const member function of the entity type that assigns the column value to an entity
    instance.

@details
    This macro is similar to the `SQT_COLUMN_ACCESSOR` macro, except that it allows specifying a 
    custom name for the column instance. This is useful in scenarios where the auto-generated
    instance name would conflict with other names generated by the framework.
    
@see SQT_COLUMN_ACCESSOR
@see SQT_COLUMN_FIELD_2
*/
#define SQT_COLUMN_ACCESSOR_2(COLUMN_NAME, INSTANCE_NAME, GETTER, SETTER) \
__SQT_COLUMN_BEGIN(COLUMN_NAME, INSTANCE_NAME) \
__SQT_VALUE_SOURCE_ACCESSOR(GETTER, SETTER) \
__SQT_COLUMN_END(COLUMN_NAME, INSTANCE_NAME)


/**
Defines a column that binds to the specified custom value source.

@param COLUMN_NAME
    The name of the column in the database. It will be also used as the instance name of the 
    column.

@param VALUE_SOURCE
    A type that satisfies the `sqt::ValueSourceType` concept, which defines the value type and 
    methods for retrieving and setting values in an entity instance.

@details
    This macro is similar to `SQT_COLUMN_FIELD`, except that it binds to a custom value source. It
    is useful if the column value is not directly accessible through a field or accessor methods. 
    For example, the column value may be derived from multiple fields or requires some computation 
    or transformation before getting or setting it.

    The `sqt::ValueSourceType` concept specifies the interface that a value source must implement:
    - The value type for the column.
    - Methods to retrieve and set the value in an entity instance.

    Example usage:
    @code
    struct MyEntity {
        int id{};
        std::string name;
    };

    // Define the value source type for the ID column.
    struct IDValueSource {
        using ValueType = int;
        static int GetValueFromEntity(const MyEntity& entity) {
            return entity.id;
        }
        static void SetValueToEntity(MyEntity& entity, int value) {
            entity.id = value;
        }
    };

    SQT_TABLE_BEGIN(MyEntityTable, MyEntity)

    // Define the ID column with the custom value source.
    SQT_COLUMN_CUSTOM(ID, IDValueSource)

    // Define the Name column with an inline custom value source.
    SQT_COLUMN_CUSTOM(Name, struct NameValueSource {
        using ValueType = std::string;
        static const std::string& GetValueFromEntity(const MyEntity& entity) {
            return entity.name;
        }
        static void SetValueToEntity(MyEntity& entity, std::string value) {
            entity.name = std::move(value);
        }
    })

    SQT_TABLE_END
    @endcode

@see sqt::ValueSourceType
@see SQT_COLUMN_CUSTOM_2
@see SQT_COLUMN_FIELD
*/
#define SQT_COLUMN_CUSTOM(COLUMN_NAME, VALUE_SOURCE) \
__SQT_COLUMN_BEGIN(COLUMN_NAME, COLUMN_NAME) \
__SQT_VALUE_SOURCE_CUSTOM(VALUE_SOURCE) \
__SQT_COLUMN_END(COLUMN_NAME, COLUMN_NAME)


/**
Defines a column with a custom instance name that binds to the specified custom value source.

@param COLUMN_NAME
    The name of the column in the database.

@param INSTANCE_NAME
    The name of the column instance.

@param VALUE_SOURCE
    A type that satisfies the `sqt::ValueSourceType` concept, which defines the value type and
    methods for retrieving and setting values in an entity instance.

@details
    This macro is similar to the `SQT_COLUMN_CUSTOM` macro, except that it allows specifying a 
    custom name for the column instance. This is useful in scenarios where the auto-generated
    instance name would conflict with other names generated by the framework.

@see sqt::ValueSourceType
@see SQT_COLUMN_CUSTOM
@see SQT_COLUMN_FIELD_2
*/
#define SQT_COLUMN_CUSTOM_2(COLUMN_NAME, INSTANCE_NAME, VALUE_SOURCE) \
__SQT_COLUMN_BEGIN(COLUMN_NAME, INSTANCE_NAME) \
__SQT_VALUE_SOURCE_CUSTOM(VALUE_SOURCE) \
__SQT_COLUMN_END(COLUMN_NAME, INSTANCE_NAME)


/**
Defines a primary key with the specified columns.

@param ...
    The names of the columns that form the primary key. A primary key can be composed of one or 
    more columns.

@details
    This macro must be used between the `SQT_TABLE_BEGIN` and `SQT_TABLE_END` macros and must be 
    placed after all definitions of the columns that are part of the primary key. There can be only
    one primary key definition in a table type.

    Columns of the primary key must not be nullable.

    To define an autoincrement primary key, use the `SQT_PRIMARY_KEY_AUTO_INC` macro instead.

    Example usage:
    @code
    struct MyEntity {
        int id{};
        std::string name;
    };

    SQT_TABLE_BEGIN(MyEntityTable, MyEntity)
    SQT_COLUMN_FIELD(ID, id)
    SQT_COLUMN_FIELD(Name, name)
    // Define the primary key with the ID and Name columns.
    SQT_PRIMARY_KEY(ID, Name)
    SQT_TABLE_END
    @endcode

    The following code demonstrates the generated definition of the primary key in the table type:
    @code
    class TableType {
    public:
        // Column types.
        class IDType;
        class NameType;

        // The class name of the primary key type is fixed.
        class PrimaryKeyType : public sqt::PrimaryKey<IDType, NameType> {
        public:
            // Forbids copying.
            PrimaryKeyType(const PrimaryKeyType&) = delete;
            PrimaryKeyType& operator=(const PrimaryKeyType&) = delete;

            // Forbids moving.
            PrimaryKeyType(PrimaryKeyType&&) = delete;
            PrimaryKeyType& operator=(PrimaryKeyType&&) = delete;

            // Assignment operator that generates an assignment expression.
            constexpr auto operator=(const ValueType&) const noexcept;

            // Ordering operator that generates an ordering term expression.
            constexpr auto Asc() const noexcept;
            constexpr auto Desc() const noexcept;

            // Comparison operators that generate predicate expressions.
            // Here shows only the == operator. Other operators (!=, <, <=, >, >=) are omitted.
            friend constexpr auto operator==(const PrimaryKeyType&, const ValueType&) const noexcept;
            friend constexpr auto operator==(const PrimaryKeyType&, sqt::Placeholder) const noexcept;
            friend constexpr auto operator==(const ValueType&, const PrimaryKeyType&) const noexcept;
            friend constexpr auto operator==(sqt::Placeholder, const PrimaryKeyType&) const noexcept;
        };

        // The instance of the primary key, which is defined as a public member variable of the 
        // table type. The name of the variable is fixed.
        PrimaryKeyType PrimaryKey;
    };
    @endcode

@see SQT_TABLE_BEGIN
@see SQT_COLUMN_FIELD
@see SQT_PRIMARY_KEY_AUTO_INC
@see sqt::PrimaryKey<>
*/
#define SQT_PRIMARY_KEY(...) __SQT_PRIMARY_KEY(false, __VA_ARGS__)


/**
Defines an autoincrement primary key with the specified column.

@param COLUMN_NAME
    The name of the column that forms the autoincrement primary key.

@details
    This macro is similar to `SQT_PRIMARY_KEY`, except that it defines an autoincrement primary 
    key.

    The column's value type must be an integer type.

    Example usage:
    @code
    struct MyEntity {
        int id{};
        std::string name;
    };
    SQT_TABLE_BEGIN(MyEntityTable, MyEntity)
    SQT_COLUMN_FIELD(ID, id)
    SQT_COLUMN_FIELD(Name, name)
    // Define the autoincrement primary key with the ID column.
    SQT_PRIMARY_KEY_AUTO_INC(ID)
    SQT_TABLE_END
    @endcode

@see SQT_PRIMARY_KEY
*/
#define SQT_PRIMARY_KEY_AUTO_INC(COLUMN_NAME) __SQT_PRIMARY_KEY(true, COLUMN_NAME)


/**
Defines an index with an auto-generated name based on the specified columns.

@param ...
    The names of the columns that form the index. An index can consist of up to 8 columns.

@details
    This macro must be used between the `SQT_TABLE_BEGIN` and `SQT_TABLE_END` macros and must be 
    placed after all definitions of the columns that are part of the index. There can be multiple
    index definitions in a table type.

    The index name in the database is generated using the following format:
    @code
    <TableName>_Index_<Column1>_<Column2>_...
    @endcode

    Example usage:
    @code
    struct MyEntity {
        int id{};
        std::string name;
    };

    SQT_TABLE_BEGIN(MyEntityTable, MyEntity)
    SQT_COLUMN_FIELD(ID, id)
    SQT_COLUMN_FIELD(Name, name)
    // Define an index with the ID and Name columns.
    SQT_INDEX(ID, Name)
    SQT_TABLE_END
    @endcode

    The following code demonstrates the generated definition of the index in the table type:
    @code
    class TableType {
    public:
        // Column types.
        class IDType;
        class NameType;

        // The class for the index type, whose name is generated by joining the column names with 
        // an underscore ('_') as the delimiter and appending the result to the fixed prefix 
        // "IndexType_".
        class IndexType_ID_Name :
            public sqt::CompositeColumn<IDType, NameType>,
            public sqt::AbstractIndex {

        public:
            //Forbids copying.
            IndexType_IDName(const IndexType_IDName&) = delete;
            IndexType_IDName& operator=(const IndexType_IDName&) = delete;

            //Forbids moving.
            IndexType_IDName(IndexType_IDName&&) = delete;
            IndexType_IDName& operator=(IndexType_IDName&&) = delete;

            // Assignment operator that generates an assignment expression.
            constexpr auto operator=(const ValueType&) const noexcept;

            // Ordering operator that generates an ordering term expression.
            constexpr auto Asc() const noexcept;
            constexpr auto Desc() const noexcept;

            // Comparison operators that generate predicate expressions.
            // Here shows only the == operator. Other operators (!=, <, <=, >, >=) are omitted.
            friend constexpr auto operator==(const IndexType_IDName&, const ValueType&) const noexcept;
            friend constexpr auto operator==(const IndexType_IDName&, sqt::Placeholder) const noexcept;
            friend constexpr auto operator==(const ValueType&, const IndexType_IDName&) const noexcept;
            friend constexpr auto operator==(sqt::Placeholder, const IndexType_IDName&) const noexcept;
        };

        // The instance of the index, which is defined as a public member variable of the table
        // type. The name of the variable is generated by joining the column names with an 
        // underscore ('_') as the delimiter and appending the result to the fixed prefix "Index_".
        IndexType_ID_Name Index_ID_Name;
    };
    @endcode

    The following alternative macros can also be used to define indexes:
    - `SQT_INDEX_UNIQUE`: Defines an unique index with an auto-generated name.
    - `SQT_INDEX_NAMED`: Defines an index with a custom name.
    - `SQT_INDEX_NAMED_UNIQUE`: Defines an unique index with a custom name.

@see sqt::AbstractIndex
@see sqt::CompositeColumn<>
@see SQT_TABLE_BEGIN
@see SQT_INDEX_NAMED
@see SQT_INDEX_NAMED_UNIQUE
@see SQT_INDEX_UNIQUE

@hideinitializer
*/
#define SQT_INDEX(...) __SQT_DEFINE_INDEX_AUTO_NAME(false, __VA_ARGS__)


/**
Defines an index with the specified name and columns.

@param NAME
    The name of the index. This name will be used as the index name in the database.

@param ...
    The names of the columns that form the index. An index can consist of up to 8 columns.

@details
    This macro is similar to `SQT_INDEX`, except that it allows specifying a custom name for the
    index. The index name in the database will be the same as the specified name.

    Example usage:
    @code
    struct MyEntity {
        int id{};
        std::string name;
    };
    SQT_TABLE_BEGIN(MyEntityTable, MyEntity)
    SQT_COLUMN_FIELD(ID, id)
    SQT_COLUMN_FIELD(Name, name)
    // Define an index with a custom name and the ID and Name columns.
    SQT_INDEX_NAMED(MyCustomIndex, ID, Name)
    SQT_TABLE_END
    @endcode

    The custom index name also affects the names of the index type and instance variable in the
    table type:
    - The class name of the index type will be generated by appending the specified name to the
      fixed string `IndexType_`.
    - The name of the index instance variable will be generated by appending the specifed name to 
      the fixed string `Index_`.

@see `SQT_INDEX`

@hideinitializer
*/
#define SQT_INDEX_NAMED(NAME, ...) __SQT_DEFINE_INDEX_CUSTOM_NAME(NAME, false, __VA_ARGS__)


/**
Defines an unique index with an auto-generated name based on the specified columns.

@param ...
    The names of the columns that form the unique index. An index can consist of up to 8 columns.

@details
    This macro is similar to `SQT_INDEX`, except that it defines an unique index.

    Example usage:
    @code
    struct MyEntity {
        int id{};
        std::string name;
    };
    SQT_TABLE_BEGIN(MyEntityTable, MyEntity)
    SQT_COLUMN_FIELD(ID, id)
    SQT_COLUMN_FIELD(Name, name)
    // Define an unique index with the Name column.
    SQT_INDEX_UNIQUE(Name)
    SQT_TABLE_END
    @endcode

@see SQT_INDEX

@hideinitializer
*/
#define SQT_INDEX_UNIQUE(...) __SQT_DEFINE_INDEX_AUTO_NAME(true, __VA_ARGS__)


/**
Defines an unique index with the specified name and columns.

@param NAME
    The name of the index. This name will be used as the index name in the database.

@param ...
    The names of the columns that form the index. An index can consist of up to 8 columns.

@details
    This macro is similar to `SQT_INDEX_NAMED`, except that it defines an unique index.

    Example usage:
    @code
    struct MyEntity {
        int id{};
        std::string name;
    };
    SQT_TABLE_BEGIN(MyEntityTable, MyEntity)
    SQT_COLUMN_FIELD(ID, id)
    SQT_COLUMN_FIELD(Name, name)
    // Define an unique index with a custom name and the Name column.
    SQT_INDEX_NAMED_UNIQUE(MyCustomIndex, Name)
    SQT_TABLE_END
    @endcode

@see SQT_INDEX_NAMED

@hideinitializer
*/
#define SQT_INDEX_NAMED_UNIQUE(NAME, ...) __SQT_DEFINE_INDEX_CUSTOM_NAME(NAME, true, __VA_ARGS__)

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
constexpr sqt::ColumnsView<TableEntityType> TableType::GetColumns() const noexcept { \
    return Insider::Columns; \
} \
constexpr sqt::ColumnsView<TableEntityType> TableType::GetPrimaryKeyColumns() const noexcept { \
    return sqt::internal::PrimaryKeyShim<TableType>::GetPKColumns(Insider::TableInstance); \
} \
constexpr sqt::ColumnsView<TableEntityType> TableType::GetNonPrimaryKeyColumns() const noexcept { \
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
