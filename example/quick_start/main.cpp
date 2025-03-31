#include <filesystem>
#include <iostream>
#include <sqt/orm/data_context.h>
#include <sqt/orm/table_definition.h>
#include <sqt/orm/table_mapping.h>

struct MyEntity {
    int id;
    std::string name;
};

SQT_TABLE_BEGIN(MyEntityTable, MyEntity)
// Define the ID column that binds to the id field in MyEntity.
SQT_COLUMN_FIELD(ID, id)
// Define the Name column that binds to the name field in MyEntity.
SQT_COLUMN_FIELD(Name, name)
// Define the primary key with the ID column.
SQT_PRIMARY_KEY(ID)
SQT_TABLE_END

SQT_REGISTER(MyEntityTable)

int main() {

    auto database_file_path = std::filesystem::temp_directory_path() / "MyDatabase.db";

    // Delete the previous database file before test to avoid primary key conflict.
    std::filesystem::remove(database_file_path);

    // Open a database and create a data context instance for the entity type.
    auto database = sqt::Database::Open(database_file_path);
    sqt::DataContext<MyEntity> data_context{ std::move(database) };

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
}