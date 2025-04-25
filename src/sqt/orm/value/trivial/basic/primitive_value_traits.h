#pragma once

/**
@file
    Defines the `sqt::PrimitiveValueTraits<>` primary template and its specializations for various 
    primitive value types.
*/

#include <concepts>
#include <sqt/foundation/data_type.h>
#include <sqt/foundation/statement.h>

namespace sqt {

/**
The primary template for defining traits for primitive value types.

@tparam T
    The type of the value.

@details
    This primary template is intentionally left undefined. It is used to trigger a compile-time 
    error when instantiated with a type that is not recognized as a primitive value type.
    
    There are three specializations provided for primitive value types:
    - `sqt::PrimitiveValueTraits<INTEGER>`, for integral types.
    - `sqt::PrimitiveValueTraits<FLOAT>`, for floating-point types.
    - `sqt::PrimitiveValueTraits<std::string>`, for `std::string`.

@see sqt::PrimitiveValueTraits<INTEGER>
@see sqt::PrimitiveValueTraits<FLOAT>
@see sqt::PrimitiveValueTraits<std::string>
@see sqt::PrimitiveValueType
*/
template<typename T>
class PrimitiveValueTraits;


/**
The specialization for defining traits for integral value types.

@tparam INTEGER
    A type that satisfies the `std::integral` concept.

@details
    This specialization satisfies the `sqt::BasicValueTraitsType` concept.

@see sqt::BasicValueTraitsType
@see sqt::PrimitiveValueTraits<FLOAT>
@see sqt::PrimitiveValueTraits<std::string>
*/
template<std::integral INTEGER>
class PrimitiveValueTraits<INTEGER> {
public:
    using ValueType = INTEGER;

    static constexpr sqt::DataType DataType = sqt::DataType::Integer;
    static constexpr bool IsNullable = false;

    /**
    Binds an integral value to the statement at the specified parameter index.

    @param statement
        The statement to which the value is bound.

    @param parameter_index
        The index of the parameter to which the value is bound.

    @param value
        The value to bind.

    @throw sqt::SQLError
        Thrown if the binding fails.

    @details
        Depending on the size of the integral type, a different method of the statement is used 
        to bind the value:
        - `BindParameter(int, int)` is used for types smaller than `std::int64_t`.
        - `BindParameter(int, std::int64_t)` is used for types equal to or larger than 
          `std::int64_t`.

    @see sqt::Statement::BindParameter(int, int)
    @see sqt::Statement::BindParameter(int, std::int64_t)
    */
    static void BindValue(Statement& statement, int parameter_index, INTEGER value) {
        if constexpr (sizeof(INTEGER) >= sizeof(std::int64_t)) {
            statement.BindParameter(parameter_index, static_cast<std::int64_t>(value));
        }
        else {
            statement.BindParameter(parameter_index, static_cast<int>(value));
        }
    }

    /**
    Retrieves an integral value from the statement at the specified column index.

    @param statement
        The statement from which the value is retrieved.

    @param column_index
        The index of the column from which to retrieve the value.

    @return
        The retrieved value.

    @details
        Depending on the size of the integral type, a different method of the statement is used 
        to retrieve the value:
        - `GetColumnInt()` is used for types smaller than `std::int64_t`.
        - `GetColumnInt64()` is used for types equal to or larger than `std::int64_t`.

        @warning
        The retrieved value will be truncated if the original value stored in the database exceeds 
        the maximum representable value of the integral type.

    @see sqt::Statement::GetColumnInt()
    @see sqt::Statement::GetColumnInt64()
    */
    static INTEGER RetrieveValue(const Statement& statement, int column_index) noexcept {
        if constexpr (sizeof(INTEGER) >= sizeof(std::int64_t)) {
            return static_cast<INTEGER>(statement.GetColumnInt64(column_index));
        }
        return static_cast<INTEGER>(statement.GetColumnInt(column_index));
    }
};


/**
The specialization for defining traits for floating-point value types.

@tparam FLOAT
    A type that satisfies the `std::floating_point` concept, except `long double`.

@details
    This specialization satisfies the `sqt::BasicValueTraitsType` concept.

@see sqt::BasicValueTraitsType
@see sqt::PrimitiveValueTraits<INTEGER>
@see sqt::PrimitiveValueTraits<std::string>
*/
template<std::floating_point FLOAT> requires (!std::same_as<FLOAT, long double>)
class PrimitiveValueTraits<FLOAT> {
public:
    using ValueType = FLOAT;

    static constexpr sqt::DataType DataType = sqt::DataType::Float;
    static constexpr bool IsNullable = false;

    /**
    Binds a floating-point value to the statement at the specified parameter index.

    @param statement
        The statement to which the value is bound.

    @param parameter_index
        The index of the parameter to which the value is bound.

    @param value
        The value to bind.

    @throw sqt::SQLError
        Thrown if the binding fails.

    @details
        This method uses the `BindParameter(int, double)` method of the statement to bind the 
        value.

    @see sqt::Statement::BindParameter(int, double)
    */
    static void BindValue(Statement& statement, int parameter_index, FLOAT value) {
        statement.BindParameter(parameter_index, value);
    }

    /**
    Retrieves a floating-point value from the statement at the specified column index.

    @param statement
        The statement from which the value is retrieved.

    @param column_index
        The index of the column from which to retrieve the value.

    @return
        The retrieved value.

    @details
        This method uses the `GetColumnDouble()` method to retrieve the value from the statement.

        @warning
        The retrieved value will be truncated if the original value stored in the database exceeds
        the maximum representable value of the integral type.

    @see sqt::Statement::GetColumnDouble()
    */
    static FLOAT RetrieveValue(const Statement& statement, int column_index) noexcept {
        return static_cast<FLOAT>(statement.GetColumnDouble(column_index));
    }
};


/**
The specialization for defining traits for `std::string`.

@details
    This specialization satisfies the `sqt::BasicValueTraitsType` concept.

@see sqt::BasicValueTraitsType
@see sqt::PrimitiveValueTraits<FLOAT>
@see sqt::PrimitiveValueTraits<INTEGER>
*/
template<>
class PrimitiveValueTraits<std::string> {
public:
    using ValueType = std::string;

    static constexpr sqt::DataType DataType = sqt::DataType::Text;
    static constexpr bool IsNullable = false;

    /**
    Binds a string to the statement at the specified parameter index.

    @param statement
        The statement to which the string is bound.

    @param parameter_index
        The index of the parameter to which the string is bound.

    @param value
        The string to bind.

    @throw sqt::SQLError
        Thrown if the binding fails.

    @details
        This method uses the `BindParameter(int, std::string_view)` method of the statement to bind 
        the string.

    @see sqt::Statement::BindParameter(int, std::string_view)
    */
    static void BindValue(Statement& statement, int parameter_index, const std::string& value) {
        statement.BindParameter(parameter_index, value);
    }

    /**
    Retrieves a string from the statement at the specified column index.

    @param statement
        The statement from which the string is retrieved.

    @param column_index
        The index of the column from which to retrieve the string.

    @return
        A copy of the string retrieved from the statement.

    @throw std::bad_alloc
        Thrown if the string cannot be allocated.

    @details
        This method uses the `GetColumnText()` method to retrieve the string from the statement.

    @see sqt::Statement::GetColumnText()
    */
    static std::string RetrieveValue(const Statement& statement, int column_index) {
        return std::string{ statement.GetColumnText(column_index) };
    }
};

}