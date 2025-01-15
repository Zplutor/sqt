#pragma once

#include <sqt/core/statement.h>
#include <sqt/orm/binder/binder_chain.h>
#include <sqt/orm/querier/querier_like.h>

namespace sqt {

template<QuerierLike Q>
class Executor {
public:
    Executor(Statement statement, const Q& querier) : 
        statement_(std::move(statement)),
        querier_(querier) {

    }

    auto BeginBind() {
        constexpr auto binders = Q::BuildPlaceholderBinders();
        return MakeBinderChain(statement_, binders);
    }

    bool Step() {
        return statement_.Step();
    }

private:
    Statement statement_;
    const Q& querier_;
};

}