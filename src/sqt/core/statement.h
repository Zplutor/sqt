#pragma once

#include <cstdint>
#include <optional>
#include <string_view>
#include <sqlite3.h>
#include <sqt/core/data_type.h>

namespace sqt {

class Statement {
public:
    Statement(sqlite3* database_handle, sqlite3_stmt* statement_handle) noexcept;
    ~Statement();

    Statement(const Statement&) = delete;
    Statement& operator=(const Statement&) = delete;

    Statement(Statement&& other) noexcept;
    Statement& operator=(Statement&& other) noexcept;

    void BindParameter(int parameter_index, int value);
    void BindParameter(int parameter_index, std::int64_t value);
    void BindParameter(int parameter_index, std::uint64_t value);
    void BindParameter(int parameter_index, std::string_view value);
    void BindParameter(int parameter_index, std::nullopt_t);
    void ClearBindings();

    bool Step();
    void Reset();

    DataType GetColumnType(int column_index) const noexcept;
    int GetColumnInt(int column_index) const noexcept;
    std::int64_t GetColumnInt64(int column_index) const noexcept;
    std::string_view GetColumnText(int column_index) const noexcept;

    sqlite3_stmt* Handle() const noexcept {
        return statement_handle_;
    }

private:
    void Finalize() noexcept;

private:
    sqlite3* database_handle_{};
    sqlite3_stmt* statement_handle_{};
};

}