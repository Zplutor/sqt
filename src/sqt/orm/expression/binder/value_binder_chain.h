#pragma once

#include <tuple>
#include <sqt/foundation/statement.h>
#include <sqt/orm/expression/binder/value_binder_type.h>

namespace sqt {

template<ValueBinderType... Binders>
class ValueBinderChain;

template<>
class ValueBinderChain<> {
public:
    ValueBinderChain(Statement& statement, std::tuple<>) noexcept { }
};

template<ValueBinderType FirstBinder, ValueBinderType... RestBinders>
class ValueBinderChain<FirstBinder, RestBinders...> {
public:
    ValueBinderChain(Statement& statement, std::tuple<FirstBinder, RestBinders...> binders) :
        statement_(statement),
        binders_(std::move(binders)) {

    }

    auto Bind(const typename FirstBinder::ValueType& value) {

        std::get<0>(binders_).Bind(statement_, value);

        auto rest_tuple = std::apply([](auto, auto... rest) {
            return std::make_tuple(rest...);
        }, 
        binders_);

        return ValueBinderChain<RestBinders...>(statement_, rest_tuple);
    }

private:
    std::tuple<FirstBinder, RestBinders...> binders_;
    Statement& statement_;
};


template<ValueBinderType... Binders>
auto MakeBinderChain(Statement& statement, std::tuple<Binders...> tuple) {
    return ValueBinderChain<Binders...>(statement, std::move(tuple));
}


template<typename T>
concept BinderLikeTuple = requires(T t, Statement & statement) {
    MakeBinderChain(statement, t);
};

}