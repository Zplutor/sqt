#pragma once

/**
@file
    Defines the `sqt::CompositeValueTraits<>` class template.
*/

#include <tuple>
#include <sqt/orm/value/trivial/basic/basic_value_traits_type.h>

namespace sqt {

/**
Defines traits for composite value types.

@tparam TRAITS
    A pack of types that each satisfy the `sqt::BasicValueTraitsType` concept. The pack must not be 
    empty.

@details
    This traits type is a composite of multiple basic value traits types.

    This class template satisfies the `sqt::CompositeValueTraitsType` concept.
    
@see sqt::BasicValueTraitsType
@see sqt::CompositeValueTraitsType
*/
template<BasicValueTraitsType... TRAITS>
class CompositeValueTraits {
public:
    static_assert(sizeof...(TRAITS) > 0);

    /**
    A `std::tuple<>` of basic value traits types that make up the composite value traits type.

    @details
        This tuple is constructed from the `TRAITS` type pack. All elements in the tuple satisfy 
        the `sqt::BasicValueTraitsType` concept.

    @see sqt::BasicValueTraitsType
    */
    using ValueTraitsTypes = std::tuple<TRAITS...>;

    /**
    A `std::tuple<>` of basic value types that make up the composite value type.

    @details
        The tuple is constructed from the nested `ValueType` types of each basic value traits type
        in the `TRAITS` type pack.

        All elements in the tuple satisfy the `sqt::BasicValueType` concept. This tuple itself
        satisfies the `sqt::CompositeValueType` concept.

    @see sqt::BasicValueType
    @see sqt::CompositeValueType
    */
    using ValueType = std::tuple<typename TRAITS::ValueType...>;

    /**
    Binds a composite value to the statement beginning at the specified parameter index.

    @param statement
        The statement to which the value is bound.

    @param parameter_index
        The starting index of the parameters to which the value is bound.

    @param value
        The composite value to bind.

    @throw sqt::SQLError
        Thrown if the binding fails.

    @details
        This method delegates to the `BindValue()` method of each basic value traits type in the
        `TRAITS` type pack. The parameter index is incremented for each value in the composite
        value.
    */
    static void BindValue(Statement& statement, int parameter_index, const ValueType& value) {

        std::apply(
            [&statement, parameter_index](const auto&... values) {
                int index = parameter_index;
                (TRAITS::BindValue(statement, index++, values), ...);
            },
            value);
    }

    /**
    Retrieves a composite value from the statement beginning at the specified column index.

    @param statement
        The statement from which the value is retrieved.

    @param column_index
        The starting index of the column from which to retrieve the value.

    @return
        The retrieved composite value.

    @details
        This method delegates to the `RetrieveValue()` method of each basic value traits type in 
        the `TRAITS` type pack. The column index is incremented for each value in the composite
        value.
    */
    static ValueType RetrieveValue(const Statement& statement, int column_index) {

        int index = column_index;
        return ValueType{ TRAITS::RetrieveValue(statement, index++)... };
    }
};

}