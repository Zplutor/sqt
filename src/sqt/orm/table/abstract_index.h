#pragma once

#include <span>
#include <sqt/orm/table/column/abstract_column.h>

namespace sqt {

class AbstractIndex {
public:
    constexpr AbstractIndex() noexcept = default;

    AbstractIndex(const AbstractIndex&) = delete;
    AbstractIndex& operator=(const AbstractIndex&) = delete;

    virtual std::string_view GetName() const noexcept = 0;
    virtual AbstractColumnsView GetAbstractColumns() const noexcept = 0;
    virtual bool IsUnique() const noexcept = 0;
};

using AbstractIndexesView = std::span<const AbstractIndex* const>;

}