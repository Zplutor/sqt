#pragma once

/**
@file
    Defines the `sqt::NullableValueTraits<>` class template.
*/

#include <sqt/orm/value/trivial/basic/nullable_value_type.h>
#include <sqt/orm/value/trivial/basic/primitive_value_traits.h>

namespace sqt {

/**
Defines traits for nullable value types.

@tparam T
    A type that satisfies the `sqt::NullableValueType` concept.

@details
    This traits type is a wrapper around `sqt::PrimitiveValueTraits<>`, adding support for 
    nullability.

    This class template satisfies the `sqt::BasicValueTraitsType` concept.

@see sqt::BasicValueTraitsType
@see sqt::NullableValueType
@see sqt::PrimitiveValueTraits<>
*/
template<NullableValueType T>
class NullableValueTraits {
public:
    using ValueType = T;
    using InnerValueTriats = PrimitiveValueTraits<internal::GetOptionalValueTypeT<T>>;

    static constexpr DataType DataType = InnerValueTriats::DataType;
    static constexpr bool IsNullable = true;

    /**
    Binds a nullable value to the statement at the specified parameter index.

    @param statement
        The statement to which the value is bound.

    @param parameter_index
        The index of the parameter to which the value is bound.

    @param value
        The nullable value to bind.

    @throw sqt::SQLError
        Thrown if the binding fails.

    @details
        If the value is null, this method calls the `BindParameter(int, std::nullopt_t)` method of
        the statement to bind a null. Otherwise, it delegates to the `BindValue()` method of the 
        corresponding `sqt::PrimitiveValueTraits<>` specialization to bind the underlying value.

    @see sqt::PrimitiveValueTraits<INTEGER>::BindValue()
    @see sqt::PrimitiveValueTraits<FLOAT>::BindValue()
    @see sqt::PrimitiveValueTraits<std::string>::BindValue()
    @see sqt::Statement::BindParameter(int, std::nullopt_t)
    */
    static void BindValue(Statement& statement, int parameter_index, const T& value) {
        if (value.has_value()) {
            InnerValueTriats::BindValue(statement, parameter_index, *value);
        }
        else {
            statement.BindParameter(parameter_index, std::nullopt);
        }
    }

    /**
    Retrieves a nullable value from the statement at the specified column index.

    @param statement
        The statement from which the value is retrieved.

    @param column_index
        The index of the column from which to retrieve the value.

    @return
        The retrieved value.

    @details
        If the value at the specified column index is null, this method returns `std::nullopt`. 
        Otherwise, it delegates to the `RetrieveValue()` method of the corresponding 
        `sqt::PrimitiveValueTraits<>` specialization to retrieve the underlying value.

    @see sqt::PrimitiveValueTraits<INTEGER>::RetrieveValue()
    @see sqt::PrimitiveValueTraits<FLOAT>::RetrieveValue()
    @see sqt::PrimitiveValueTraits<std::string>::RetrieveValue()
    */
    static T RetrieveValue(const Statement& statement, int column_index) {

        auto column_type = statement.GetColumnType(column_index);
        if (column_type == DataType::Null) {
            return std::nullopt;
        }

        return InnerValueTriats::RetrieveValue(statement, column_index);
    }
};

}