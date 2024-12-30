#include <sqt/core/statement.h>
#include <sqt/core/sql_error.h>

namespace sqt {

Statement::Statement(sqlite3* database_handle, sqlite3_stmt* statement_handle) noexcept :
    database_handle_(database_handle),
    statement_handle_(statement_handle) {

}


Statement::~Statement() {
    Finalize();
}


Statement::Statement(Statement&& other) noexcept : 
    database_handle_(other.database_handle_),
    statement_handle_(other.statement_handle_) {

    other.database_handle_ = nullptr;
    other.statement_handle_ = nullptr;
}


Statement& Statement::operator=(Statement&& other) noexcept {
    if (this != &other) {
        Finalize();
        database_handle_ = other.database_handle_;
        statement_handle_ = other.statement_handle_;
        other.database_handle_ = nullptr;
        other.statement_handle_ = nullptr;
    }
    return *this;
}


void Statement::Finalize() noexcept {
    if (statement_handle_) {
        sqlite3_finalize(statement_handle_);
        statement_handle_ = nullptr;
    }
}


void Statement::BindParameter(int parameter_index, int value) {
    int error_code = sqlite3_bind_int(statement_handle_, parameter_index, value);
    SQT_THROW_IF_SQL_ERROR(error_code, database_handle_);
}


void Statement::BindParameter(int parameter_index, std::int64_t value) {
    int error_code = sqlite3_bind_int64(statement_handle_, parameter_index, value);
    SQT_THROW_IF_SQL_ERROR(error_code, database_handle_);
}


void Statement::BindParameter(int parameter_index, std::uint64_t value) {
    BindParameter(parameter_index, static_cast<std::int64_t>(value));
}


void Statement::BindParameter(int parameter_index, std::string_view value) {

    int error_code = sqlite3_bind_text(
        statement_handle_,
        parameter_index, 
        value.data(),
        static_cast<int>(value.length()),
        SQLITE_STATIC);

    SQT_THROW_IF_SQL_ERROR(error_code, database_handle_);
}


void Statement::BindParameter(int parameter_index, std::nullopt_t) {
    int error_code = sqlite3_bind_null(statement_handle_, parameter_index);
    SQT_THROW_IF_SQL_ERROR(error_code, database_handle_);
}


void Statement::ClearBindings() {
    int error_code = sqlite3_clear_bindings(statement_handle_);
    SQT_THROW_IF_SQL_ERROR(error_code, database_handle_);
}


bool Statement::Step() {

    int error_code = sqlite3_step(statement_handle_);
    if (error_code == SQLITE_ROW) {
        return true;
    }

    if (error_code == SQLITE_DONE) {
        return false;
    }

    ThrowSQLError(error_code, database_handle_);
}


void Statement::Reset() {
    int error_code = sqlite3_reset(statement_handle_);
    SQT_THROW_IF_SQL_ERROR(error_code, database_handle_);
}


DataType Statement::GetColumnType(int column_index) const noexcept {
    return static_cast<DataType>(sqlite3_column_type(statement_handle_, column_index));
}


int Statement::GetColumnInt(int column_index) const noexcept {
    return sqlite3_column_int(statement_handle_, column_index);
}


std::int64_t Statement::GetColumnInt64(int column_index) const noexcept {
    return sqlite3_column_int64(statement_handle_, column_index);
}


std::string_view Statement::GetColumnText(int column_index) const noexcept {

    int length = sqlite3_column_bytes(statement_handle_, column_index);
    auto text = sqlite3_column_text(statement_handle_, column_index);

    return std::string_view{ 
        reinterpret_cast<const char*>(text), 
        static_cast<std::size_t>(length) 
    };
}

}