#pragma once

#include <span>
#include <sqt/core/data_type.h>

namespace sqt {

class AbstractColumn {
public:
    constexpr AbstractColumn() = default;

    AbstractColumn(const AbstractColumn&) = delete;
    AbstractColumn& operator=(const AbstractColumn&) = delete;

    virtual std::string_view GetName() const noexcept = 0;
    virtual DataType GetDataType() const noexcept = 0;
    virtual bool IsNullable() const noexcept = 0;
};

using AbstractColumnsView = std::span<const AbstractColumn* const>;

}
