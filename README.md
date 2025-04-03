# SQT - Structural Query Templates

## Introduction

SQT (Structural Query Templates) is a C++ ORM (Object-Relational Mapping) framework for interacting with SQLite databases.

SQT is currently developed and tested on Windows with MSVC. While it is theoretically compatible with other compilers and platforms, it has not yet been tested outside this environment.

## Quick Start

### 1. Define the entity type

Define a struct or class for your entity, where each field corresponds to a column in the database table.

```cpp
struct MyEntity {
    int id;
    std::string name;
};
```

### 2. Define the table type

Use SQT macros to define the table type, which provides metadata for mapping the entity type to a corresponding database table.

```cpp
SQT_TABLE_BEGIN(MyEntityTable, MyEntity)

// Define the ID column that binds to the id field in MyEntity.
SQT_COLUMN_FIELD(ID, id) 

// Define the Name column that binds to the name field in MyEntity.
SQT_COLUMN_FIELD(Name, name)

// Define the primary key with the ID column.
SQT_PRIMARY_KEY(ID)

SQT_TABLE_END
```

### 3. Register the table type

Register the table type to enable ORM functionality for the entity type.

```cpp
SQT_REGISTER(MyEntityTable)
```

### 4. Use the data context

Create a data context for database operations. This provides the ability to insert, update, delete, and query rows.

```cpp
// Open a database and create a data context instance for the entity type.
auto database = std::make_shared<sqt::Database>(sqt::Database::Open("MyDatabase.db"));
sqt::DataContext<MyEntity> data_context{ database };

// Insert rows into the database.
data_context.Insert(MyEntity{ 1, "The first entity" });
data_context.Insert(MyEntity{ 2, "The second entity" });
data_context.Insert(MyEntity{ 3, "The third entity" });

// Update an existing row.
data_context.Update(MyEntity{ 3, "THE THIRD ENTITY" });

// Delete a row.
data_context.Delete(2);

// Select a row by primary key.
std::optional<MyEntity> entity = data_context.Select(1);
if (entity) {
    std::cout << "Select() result: " << entity->id << ',' << entity->name << "\n";
}

// Select all rows.
std::vector<MyEntity> all_entities = data_context.SelectAll();
std::cout << "SelectAll() result:\n";
for (const auto& each_entity : all_entities) {
    std::cout << each_entity.id << ',' << each_entity.name << "\n";
}
```