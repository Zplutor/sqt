#pragma once

#include <tuple>
#include <sqt/core/statement.h>

namespace sqt {

template<typename... Binders>
class BinderChain;

template<>
class BinderChain<> {
public:
    BinderChain(Statement& statement, std::tuple<>) noexcept { }
};

template<typename FirstBinder, typename... RestBinders>
class BinderChain<FirstBinder, RestBinders...> {
public:
    BinderChain(Statement& statement, std::tuple<FirstBinder, RestBinders...> binders) :
        statement_(statement),
        binders_(std::move(binders)) {

    }

    auto Bind(const typename FirstBinder::ValueType& value) {

        std::get<0>(binders_).Bind(statement_, value);

        auto rest_tuple = std::apply([](auto, auto... rest) {
            return std::make_tuple(rest...);
        }, 
        binders_);

        return BinderChain<RestBinders...>(statement_, rest_tuple);
    }

private:
    std::tuple<FirstBinder, RestBinders...> binders_;
    Statement& statement_;
};


template<typename... Binders>
auto MakeBinderChain(Statement& statement, std::tuple<Binders...> tuple) {
    return BinderChain<Binders...>(statement, std::move(tuple));
}

}