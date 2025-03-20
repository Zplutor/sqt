#pragma once

#include <sqt/foundation/statement.h>
#include <sqt/orm/querier/selecter/selecter_type.h>

namespace sqt {

template<SelecterType SELECTER>
class Iterator {
public:
    using iterator_category = std::input_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = SELECTER::ResultElementType;

public:
    Iterator() noexcept : statement_(nullptr) {

    }

    explicit Iterator(Statement* statement) : statement_(statement) {
        MoveNext();
    }

    Iterator& operator++() {
        MoveNext();
        return *this;
    }

    Iterator operator++(int) {
        auto temp = *this;
        ++(*this);
        return temp;
    }

    value_type operator*() const {
        return SELECTER::GetResultElement(*statement_);
    }

    friend bool operator==(const Iterator& iterator1, const Iterator& iterator2) noexcept {
        return iterator1.statement_ == iterator2.statement_;
    }

    friend bool operator!=(const Iterator& iterator1, const Iterator& iterator2) noexcept {
        return !(iterator1 == iterator2);
    }

private:
    void MoveNext() {
        if (!statement_->Step().HasMore()) {
            statement_ = nullptr;
        }
    }

private:
    Statement* statement_{};
};

}