#pragma once

/**
@file
    Defines the `sqt::Executor<>` class template.
*/

#include <sqt/foundation/statement.h>
#include <sqt/orm/executor/result.h>
#include <sqt/orm/expression/binder/value_binder_chain.h>
#include <sqt/orm/querier/querier_type.h>

namespace sqt {

template<QuerierType QUERIER>
class Executor {
public:
    Executor(Statement statement, std::shared_ptr<Database> database) noexcept :
        statement_(std::move(statement)),
        database_(std::move(database)) {

    }

    Executor(const Executor&) = delete;
    Executor& operator=(const Executor&) = delete;

    Executor(Executor&&) noexcept = default;
    Executor& operator=(Executor&&) noexcept = default;

    auto BeginBind() {
        constexpr auto binders = QUERIER::BuildPlaceholderBinders();
        return MakeBinderChain(statement_, binders);
    }

    void Execute() requires !SelecterType<QUERIER> {
        statement_.Step();
    }

    std::size_t LastChanges() const requires !SelecterType<QUERIER> {
        return database_->LastChanges();
    }

    std::int64_t LastInsertRowID() const requires !SelecterType<QUERIER> {
        return database_->LastInsertRowID();
    }
    
    [[nodiscard]]
    auto Execute() requires SelecterType<QUERIER> {
        return sqt::Result<QUERIER>{ statement_ };
    }

    void Reset() {
        statement_.Reset();
    }

private:
    Statement statement_;
    std::shared_ptr<Database> database_;
};

}