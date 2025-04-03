#pragma once

/**
@file
    Defines the `sqt::Statement` class.
*/

#include <cstdint>
#include <optional>
#include <span>
#include <string_view>
#include <sqlite3.h>
#include <sqt/foundation/data_type.h>
#include <sqt/foundation/step_result.h>

namespace sqt {

/**
Wrapper class for SQLite statement.
*/
class Statement {
public:
    /**
    Constructs an instance with the specified SQLite statement handle and database handle.

    @param statement_handle
        The SQLite statement handle. The ownership of the handle is transferred to the constructed
        instance.

    @param database_handle
        The SQLite database handle. The ownership of the handle isn't changed.
    */
    Statement(sqlite3_stmt* statement_handle, sqlite3* database_handle) noexcept;

    /**
    Destructs the instance.

    @details
        The SQLite statement handle will be finalized.
    */
    ~Statement();

    Statement(const Statement&) = delete;
    Statement& operator=(const Statement&) = delete;

    Statement(Statement&& other) noexcept;
    Statement& operator=(Statement&& other) noexcept;

    /**
    Binds the specified `int` value to the parameter at the specified index.

    @param parameter_index
        The index of the parameter at where the value is bound.

    @param value
        The value to bind.

    @throw sqt::SQLError
        Thrown if fails to bind the value.
    */
    void BindParameter(int parameter_index, int value);

    /**
    Binds the specified `std::int64_t` value to the parameter at the specified index.

    @param parameter_index
        The index of the parameter at where the value is bound.

    @param value
        The value to bind.

    @throw sqt::SQLError
        Thrown if fails to bind the value.
    */
    void BindParameter(int parameter_index, std::int64_t value);

    /**
    Binds the specified `double` value to the parameter at the specified index.

    @param parameter_index
        The index of the parameter at where the value is bound.

    @param value
        The value to bind.

    @throw sqt::SQLError
        Thrown if fails to bind the value.
    */
    void BindParameter(int parameter_index, double value);

    /**
    Binds the specified UTF-8 encoded string to the parameter at the specified index.

    @param parameter_index
        The index of the parameter at where the string is bound.

    @param string
        The string to bind. The string is copied to the statement.

    @throw sqt::SQLError
        Thrown if fails to bind the string.
    */
    void BindParameter(int parameter_index, std::string_view string);

    /**
    Binds the specified bytes as a BLOB to the parameter at the specified index.

    @param parameter_index
        The index of the parameter at where the bytes is bound.

    @param bytes
        The span of bytes to bind. The bytes are copied to the statement.

    @throw sqt::SQLError
        Thrown if fails to bind the bytes.
    */
    void BindParameter(int parameter_index, std::span<const std::byte> bytes);

    /**
    Binds a null value to the parameter at the specified index.

    @param parameter_index
        The index of the parameter at where the null value is bound.

    @param null
        The null value to bind.

    @throw sqt::SQLError
        Thrown if fails to bind the null value.
    */
    void BindParameter(int parameter_index, std::nullopt_t null);

    /**
    Clears all parameter bindings in the statement.

    @throw sqt::SQLError
        Thrown if fails to clear the bindings.

    @details
        All parameters are set to null value after being cleared.
    */
    void ClearBindings();

    /**
    Executes the statement or steps forward.

    @return
        A `sqt::StepResult` instance used to check whether the statement has more rows to step 
        forward.

    @throw sqt::SQLError
        Thrown if fails to execute or step forward.
    */
    StepResult Step();

    /**
    Resets the statement to its initial state, ready to be re-executed.

    @throw sqt::SQLError
        Thrown if fails to reset the statement.

    @details
        Reseting the statement doesn't clear the parameter bindings, use `ClearBindings` to clear
        the bindings.

    @see
        sqt::Statement::ClearBindings()
    */
    void Reset();

    /**
    Gets the data type of the column at the specified index from the current selected row.

    @param column_index
        The index of the column.

    @return
        The data type of the column.
    */
    DataType GetColumnType(int column_index) const noexcept;

    /**
    Gets an `int` value from the column at the specified index from the current selected row.

    @param column_index
        The index of the column.

    @return
        The `int` value from the column.
    */
    int GetColumnInt(int column_index) const noexcept;

    /**
    Gets a `std::int64_t` value from the column at the specified index from the current selected 
    row.

    @param column_index
        The index of the column.

    @return
        The `std::int64_t` value from the column.
    */
    std::int64_t GetColumnInt64(int column_index) const noexcept;

    /**
    Gets a `double` value from the column at the specified index from the current selected row.

    @param column_index
        The index of the column.

    @return
        The `double` value from the column.
    */
    double GetColumnDouble(int column_index) const noexcept;

    /**
    Gets an UTF-8 encoded string from the column at the specified index from the current selected 
    row.

    @param column_index
        The index of the column.

    @return
        The UTF-8 encoded string from the column. The string is a view of the column data and will
        be invalidated after the statement steps forward, is reset or destroyed.
    */
    std::string_view GetColumnText(int column_index) const noexcept;

    /**
    Gets a span of bytes from the column at the specified index from the current selected row.

    @param column_index
        The index of the column.

    @return
        The span of bytes from the column. The bytes are a view of the column data and will be
        invalidated after the statement steps forward, is reset or destroyed.
    */
    std::span<const std::byte> GetColumnBLOB(int column_index) const noexcept;

    /**
    Gets the SQLite statement handle.

    @return
        The SQLite statement handle.
    */
    sqlite3_stmt* Handle() const noexcept {
        return statement_handle_;
    }

private:
    void Finalize() noexcept;

private:
    sqlite3_stmt* statement_handle_{};
    sqlite3* database_handle_{};
};

}