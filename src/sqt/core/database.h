#pragma once

#include <filesystem>
#include <sqlite3.h>
#include <sqt/core/index_info.h>
#include <sqt/core/statement.h>
#include <sqt/core/transaction.h>
#include <sqt/core/table_info.h>

namespace sqt {

class Database {
public:
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