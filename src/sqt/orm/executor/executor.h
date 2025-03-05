#pragma once

#include <sqt/foundation/database.h>
#include <sqt/foundation/statement.h>
#include <sqt/orm/executor/result.h>
#include <sqt/orm/expression/binder/value_binder_chain.h>
#include <sqt/orm/querier/querier_type.h>

namespace sqt {

template<QuerierType QUERIER>
class Executor {
public:
    Executor(
        const QUERIER& querier, 
        std::shared_ptr<Database> database, 
        Statement statement) noexcept 
        :
        querier_(querier),
        database_(std::move(database)),
        statement_(std::move(statement)) {

    }

    Executor(const Executor&) = delete;
    Executor& operator=(const Executor&) = delete;

    Executor(Executor&&) noexcept = default;
    Executor& operator=(Executor&&) noexcept = default;

    auto BeginBind() {
        constexpr auto binders = QUERIER::BuildPlaceholderBinders();
        return MakeBinderChain(statement_, binders);
    }

    std::size_t Execute() requires !SelecterType<QUERIER> {
        statement_.Step();
        return database_->LastChanges();
    }
    
    [[nodiscard]]
    auto Execute() requires SelecterType<QUERIER> {
        return sqt::Result<QUERIER>{ statement_ };
    }

    void Reset() {
        statement_.Reset();
    }

private:
    const QUERIER& querier_;
    std::shared_ptr<Database> database_;
    Statement statement_;
};

}