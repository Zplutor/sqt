#pragma once

#include <sqt/orm/executor/iterator.h>
#include <sqt/orm/querier/selecter/selecter_type.h>

namespace sqt {

template<SelecterType SELECTER>
class Result {
public:
    using ValueType = SELECTER::ResultElementType;
    using iterator = Iterator<SELECTER>;
    using const_iterator = iterator;

public:
    explicit Result(Statement& statement) noexcept : statement_(statement) {

    }

    iterator begin() const {
        return iterator{ &statement_ };
    }

    iterator end() const noexcept {
        return iterator{};
    }

    const_iterator cbegin() const {
        return begin();
    }

    const_iterator cend() const noexcept {
        return end();
    }

private:
    Statement& statement_;
};

}