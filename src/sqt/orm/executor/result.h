#pragma once

#include <sqt/orm/executor/iterator.h>
#include <sqt/orm/querier/selecter/selecter_like.h>

namespace sqt {

template<SelecterLike SELECTER>
class Result {
public:
    using iterator = Iterator<SELECTER>;
    using const_iterator = iterator;

public:
    explicit Result(Statement& statement) noexcept : statement_(statement) {

    }

    iterator begin() {
        return iterator{ &statement_ };
    }

    iterator end() const {
        return iterator{ nullptr };
    }

    const_iterator cbegin() {
        return begin();
    }

    const_iterator cend() const {
        return end();
    }

private:
    Statement& statement_;
};

}