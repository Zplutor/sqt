#pragma once

#include <sqt/core/database.h>
#include <sqt/orm/executor/executor.h>
#include <sqt/orm/querier/selecter/entity_selecter.h>
#include <sqt/orm/table_mapping.h>

namespace sqt {

template<typename E>
class DataContext {
public:
    static constexpr auto MakeSelecter() noexcept {
        return EntitySelecter<E>{};
    }

public:
    explicit DataContext(std::shared_ptr<Database> db) noexcept : db_(std::move(db)) {

    }

    template<typename Q>
    auto Prepare(const Q& querier) {

        auto statement = db_->PrepareStatement(querier.BuildSQL());
        querier.BindInlineParameters(statement);

        return Executor{ std::move(statement), querier };
    }

private:
    std::shared_ptr<Database> db_;
};

}