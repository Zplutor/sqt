#pragma once

/**
@file
    Defines the `sqt::Result<>` class template.
*/

#include <deque>
#include <list>
#include <vector>
#include <sqt/orm/executor/iterator.h>
#include <sqt/orm/querier/selecter/selecter_type.h>

namespace sqt {

/**
Represents the result of a selecter, providing interfaces to retrieve the result elements.

@tparam SELECTER
    The selecter type on which this result is based. The type of the result elements is 
    determined by the selecter type.

@details
    A `sqt::Result<>` instance is returned by the `sqt::Executor<>::Execute()` method when a 
    selecter is used as the argument. It provides a container-like interface to iterate over the 
    result elements. 
    
    The type of the result elements is determined by the selecter type. The following list is the 
    possible result element types:
    - The entity type, if the selecter is created by the `sqt::DataContext::MakeSelecter()` 
      method.
    - A composite value type (a `std::tuple<>` of the specified columns' value types), if the
      selecter is created by the `sqt::DataContext::MakeSelecter(const COLUMNS&&...)` method.

    The `sqt::Result<>` instances are intended to be one-time use only. Do not store the instances 
    for any purpose. If the same query needs to be executed again, reset the executor and execute
    again to create a new `sqt::Result<>` instance.

@see sqt::DataContext<>
@see sqt::Executor<>
@see sqt::SelecterType
*/
template<SelecterType SELECTER>
class Result {
public:
    /**
    The type of the result elements, which is determined by the selecter type.
    */
    using value_type = SELECTER::ResultElementType;

    /**
    The type of the iterator used to iterate over the result elements.
    */
    using iterator = Iterator<SELECTER>;

    /**
    The type of the const iterator, which is the same as `iterator`.
    */ 
    using const_iterator = iterator;

public:
    /**
    Constructs a result instance.

    @param statement
        The statement associated with the result instance.

    @details
        This method is called internally by the `sqt::Executor::Execute()` method to create a
        result. It is not intended to be called directly by users.

    @see sqt::Executor<>::Execute()
    */
    explicit Result(Statement& statement) noexcept : statement_(statement) {

    }

    Result(Result&) = delete;
    Result& operator=(const Result&) = delete;

    /**
    Creates an iterator pointing to the beginning of the result elements.

    @return
        An iterator pointing to the first result element. If the result is empty, the iterator will
        be the same as the iterator returned by `end()`.

    @throw sqt::SQLError
        Thrown if the creation of the iterator fails, typically due to a failure in the underlying 
        query execution.

    @details
        The execution of the `SELECT` statement is deferred until this method is called. If the 
        execution fails, a `sqt::SQLError` exception will be thrown.

        @warning
        This method is intended to be called only once per result instance. To retrieve the result 
        again, the executor must be reset and executed to create a new result instance.
    */
    iterator begin() const {
        return iterator{ statement_ };
    }

    /**
    Creates an iterator pointing to the end of the result elements.

    @return
        An iterator pointing to the end of the result elements.
    */
    iterator end() const noexcept {
        return iterator{ statement_, std::monostate{} };
    }

    /**
    @copydoc begin()
    */
    const_iterator cbegin() const {
        return begin();
    }

    /**
    @copydoc end()
    */
    const_iterator cend() const noexcept {
        return end();
    }

    /**
    Converts all result elements to a `std::vector`.

    @return
        A `std::vector` contains all result elements.

    @throw sqt::SQLError
        Thrown if the iteration over the result fails.

    @details
        This method is a shorthand for iterating over all elements in the result and storing them 
        in a `std::vector`.

        @warning
        The result instance is consumed after the conversion and cannot be used again.

    @see sqt::Result<>::begin()
    @see sqt::Result<>::ToDeque()
    @see sqt::Result<>::ToList()
    */
    std::vector<value_type> ToVector() const {
        return To<std::vector<value_type>>();
    }

    /**
    Converts all result elements to a `std::list`.

    @return
        A `std::list` contains all result elements.

    @throw sqt::SQLError
        Thrown if the iteration over the result fails.

    @details
        This method is a shorthand for iterating over all elements in the result and storing them
        in a `std::list`.

        @warning
        The result instance is consumed after the conversion and cannot be used again.

    @see sqt::Result<>::begin()
    @see sqt::Result<>::ToDeque()
    @see sqt::Result<>::ToVector()
    */
    std::list<value_type> ToList() const {
        return To<std::list<value_type>>();
    }

    /**
    Converts all result elements to a `std::deque`.

    @return
        A `std::deque` contains all result elements.

    @throw sqt::SQLError
        Thrown if the iteration over the result fails.

    @details
        This method is a shorthand for iterating over all elements in the result and storing them
        in a `std::deque`.

        @warning
        The result instance is consumed after the conversion and cannot be used again.

    @see sqt::Result<>::begin()
    @see sqt::Result<>::ToList()
    @see sqt::Result<>::ToVector()
    */
    std::deque<value_type> ToDeque() const {
        return To<std::deque<value_type>>();
    }

private:
    template<typename CONTAINER>
    CONTAINER To() const {
        CONTAINER result;
        for (auto&& each_value : *this) {
            result.push_back(std::move(each_value));
        }
        return result;
    }

private:
    Statement& statement_;
};

}