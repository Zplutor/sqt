#pragma once

#include <span>
#include <sqt/foundation/statement.h>
#include <sqt/orm/table/column/abstract_column.h>

namespace sqt {

template<typename ENTITY>
class Column : public AbstractColumn {
public:
    using EntityType = ENTITY;

public:
    constexpr Column() noexcept = default;

    virtual void BindValueFromEntity(
        Statement& statement,
        int parameter_index,
        const ENTITY& entity) const = 0;

    virtual void RetrieveValueToEntity(
        const Statement& statement,
        int index,
        ENTITY& entity) const = 0;
};


template<typename ENTITY>
using ColumnsView = std::span<const Column<ENTITY>* const>;

}