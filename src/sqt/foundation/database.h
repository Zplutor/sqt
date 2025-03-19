#pragma once

/**
@file
    Defines the class `sqt::Database`.
*/

#include <filesystem>
#include <sqlite3.h>
#include <sqt/foundation/index_info.h>
#include <sqt/foundation/statement.h>
#include <sqt/foundation/transaction.h>
#include <sqt/foundation/table_info.h>

namespace sqt {

/**
A wrapper class for SQLite database.
*/
class Database {
public:
    /**
    Opens a SQLite database at the specified file path.

    @param path
        The file path at which the database opens. The file will be created if it doesn't exist.

    @return
        An opened `sqt::Database` instance.

    @throws sqt::SQLError
        Thrown if fails to open the database.
    */
    static Database Open(const std::filesystem::path& path);

public:
    explicit Database(sqlite3* handle) noexcept;
    ~Database();

    Database(Database&) = delete;
    Database& operator=(const Database&) = delete;

    Database(Database&& other) noexcept;
    Database& operator=(Database&& other) noexcept;

    void ExecuteSQL(std::string_view sql);

    Statement PrepareStatement(std::string_view sql);

    std::int64_t LastInsertRowID() const;
    std::size_t LastChanges() const;

    std::optional<TableInfo> GetTableInfo(std::string_view table_name);
    std::optional<IndexInfo> GetIndexInfo(std::string_view index_name);

    sqlite3* Handle() const noexcept {
        return handle_;
    }

private:
    void Reset() noexcept;

private:
    sqlite3* handle_{};
};

}