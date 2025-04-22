#pragma once

/**
@file
    Defines the `sqt::Iterator<>` class template.
*/

#include <sqt/foundation/statement.h>
#include <sqt/orm/querier/selecter/selecter_type.h>

namespace sqt {

/**
Represents the iterator used by `sqt::Result<>` to iterate over the result elements of a selecter.

@tparam SELECTER
    The selecter type on which this iterator is based. The type of the result elements is
    determined by the selecter type.

@details
    The `sqt::Iterator<>` satisfies the `std::input_iterator` concept. It is a single-pass 
    iterator, meaning that it can only advance forward and cannot move backward.

@see sqt::Result<>
@see sqt::SelecterType
*/
template<SelecterType SELECTER>
class Iterator {
public:
    using iterator_category = std::input_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = SELECTER::ResultElementType;

public:
    /**
    Constructs an iterator pointing to the beginning of the result elements.

    @param statement
        The statement associated with the iterator.

    @throw sqt::SQLError
        Thrown if the underlying statement execution fails.

    @details
        This constructor is called internally by the `sqt::Result::begin()` method to create an
        interator pointing to the first result element. It is not intended to be called directly by
        users.

        This constructor executes the `SELECT` statement. If the execution succeeds and the result
        is empty, the iterator will be set to the end state.

    @see sqt::Iterator<>::Iterator(Statement&, std::monostate)
    @see sqt::Result<>::begin()
    */
    explicit Iterator(Statement& statement) : statement_(&statement), is_end_(false) {
        MoveNext();
    }

    /**
    Constructs an iterator pointing to the end of the result elements.

    @param statement
        The statement associated with the iterator.

    @param dumb
        A dummy parameter to differentiate this constructor from the other one.

    @details
        This constructor is called internally by the `sqt::Result::end()` method to create an
        interator pointing to the end of the result elements. It is not intended to be called 
        directly by users.

        @warning
        Calling any operator or method except comparison operators on this iterator will result in
        undefined behavior.

    @see sqt::Iterator<>::Iterator(Statement&)
    @see sqt::Result<>::end()
    */
    Iterator(Statement& statement, std::monostate dumb) noexcept : 
        statement_(&statement), 
        is_end_(true) {

    }

    /**
    Advances the iterator to the next result element.

    @return
        The iterator itself.

    @throw sqt::SQLError
        Thrown if the underlying statement execution fails.

    @details
        This method moves the cursor of the `SELECT` statement to the next result element. If there
        are no more result elements, the iterator will be set to the end state.

    @see sqt::Iterator<>::Iterator(Statement&, std::monostate)
    */
    Iterator& operator++() {
        MoveNext();
        return *this;
    }

    /**
    Advances the iterator to the next result element.

    @throw sqt::SQLError
        Thrown if the underlying statement execution fails.

    @details
        This is the post-increment operator syntax. It is equivalent to calling the pre-increment 
        operator.

    @see sqt::Iterator<>::operator++()
    */
    void operator++(int) {
        ++(*this);
    }

    /**
    Retrieves the current result element pointed by the iterator.

    @return
        A new result element of the type specified by the selecter.

    @throw ..
        Any exception thrown during the construction of the result element.

    @details
        This method retrieves data from the statement and creates a new result element each type it
        is called, even if the position of the iterator is not changed. Avoid calling this method
        repeatedly if the construction of the result element is expensive.
    */
    value_type operator*() const {
        return SELECTER::GetResultElement(*statement_);
    }

    friend bool operator==(const Iterator& iterator1, const Iterator& iterator2) noexcept {
        return iterator1.is_end_ == iterator2.is_end_;
    }

    friend bool operator!=(const Iterator& iterator1, const Iterator& iterator2) noexcept {
        return !(iterator1 == iterator2);
    }

private:
    void MoveNext() {
        if (!statement_->Step().HasMore()) {
            is_end_ = true;
        }
    }

private:
    Statement* statement_{};
    bool is_end_{ true };
};

}