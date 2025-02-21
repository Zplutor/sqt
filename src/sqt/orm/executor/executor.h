#pragma once

#include <sqt/foundation/statement.h>
#include <sqt/orm/expression/binder/value_binder_chain.h>
#include <sqt/orm/executor/result.h>
#include <sqt/orm/querier/querier_like.h>

namespace sqt {

template<QuerierLike QUERIER>
class Executor {
public:
    Executor(const QUERIER& querier, Statement statement) noexcept :
        querier_(querier),
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

    void Execute() requires !SelecterLike<QUERIER> {
        statement_.Step();
    }

    auto Result() requires SelecterLike<QUERIER> {
        return sqt::Result<QUERIER>{ statement_ };
    }

    void Reset() {
        statement_.Reset();
    }

private:
    const QUERIER& querier_;
    Statement statement_;
};

}