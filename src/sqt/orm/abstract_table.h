#pragma

#include <string_view>
#include <sqt/orm/abstract_column.h>

namespace sqt {

class AbstractTable {
public:
    constexpr AbstractTable() = default;

    AbstractTable(const AbstractTable&) = delete;
    AbstractTable& operator=(const AbstractTable&) = delete;

    virtual std::string_view GetName() const noexcept = 0;
    virtual AbstractColumnsView GetAbstractColumns() const noexcept = 0;
};

}