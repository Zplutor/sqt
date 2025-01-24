#pragma once

#include <sqt/orm/table/abstract_column.h>

namespace sqt {

class AbstractPrimaryKey {
public:
    constexpr AbstractPrimaryKey() = default;

    AbstractPrimaryKey(const AbstractPrimaryKey&) = delete;
    AbstractPrimaryKey& operator=(const AbstractPrimaryKey&) = delete;

    virtual AbstractColumnsView GetAbstractColumns() const noexcept = 0;
    virtual bool IsAutoincrement() const noexcept = 0;
};

}