#include <sqt/orm/table_definition.h>
#include <sqt/orm/table_mapping.h>

// Entity and table are both defined in the global scope.
struct TableDefScopeTest_BothGlobal_Entity {};

SQT_TABLE_BEGIN(BothGlobal_Table, TableDefScopeTest_BothGlobal_Entity)
SQT_TABLE_END

SQT_REGISTER(BothGlobal_Table)

static_assert(std::is_same_v<
    sqt::TableType<TableDefScopeTest_BothGlobal_Entity>::EntityType, 
    TableDefScopeTest_BothGlobal_Entity>);


// Entity and table are both defined in the same scope.
namespace both_same_scope {
struct Entity {};

SQT_TABLE_BEGIN(BothSameScope_Table, Entity)
SQT_TABLE_END
}

SQT_REGISTER(both_same_scope::BothSameScope_Table)

static_assert(std::is_same_v<
    ::sqt::TableType<both_same_scope::Entity>::EntityType,
    both_same_scope::Entity>);


// Entity define in the global scope, table define in the namespace scope.
struct TableDefScopeTest_TableInScope_Entity {};

namespace table_in_scope {
SQT_TABLE_BEGIN(TableInScope_Table, TableDefScopeTest_TableInScope_Entity)
SQT_TABLE_END
}

SQT_REGISTER(table_in_scope::TableInScope_Table)

static_assert(std::is_same_v<
    sqt::TableType<TableDefScopeTest_TableInScope_Entity>::EntityType,
    TableDefScopeTest_TableInScope_Entity>);


// Entity define in the namespace scope, table define in the global scope.
namespace entity_in_scope {
struct Entity {};
}

SQT_TABLE_BEGIN(EntityInScope_Table, entity_in_scope::Entity)
SQT_TABLE_END

SQT_REGISTER(EntityInScope_Table)

static_assert(std::is_same_v<
    sqt::TableType<entity_in_scope::Entity>::EntityType,
    entity_in_scope::Entity>);


// Entity and table are both defined in the same scope, but in different namespaces.
namespace diff_scope_entity {
struct Entity {};
}

namespace diff_scope_table {
SQT_TABLE_BEGIN(DiffScope_Table, diff_scope_entity::Entity)
SQT_TABLE_END
}

SQT_REGISTER(diff_scope_table::DiffScope_Table)

static_assert(std::is_same_v<
    sqt::TableType<diff_scope_entity::Entity>::EntityType,
    diff_scope_entity::Entity>);


// Define table in the anonymous namespace.
namespace {
struct AnonymousScope_Entity {};

SQT_TABLE_BEGIN(AnonymousScope_Table, AnonymousScope_Entity)
SQT_TABLE_END
}

SQT_REGISTER(AnonymousScope_Table)

static_assert(std::is_same_v<
    sqt::TableType<AnonymousScope_Entity>::EntityType,
    AnonymousScope_Entity>);
