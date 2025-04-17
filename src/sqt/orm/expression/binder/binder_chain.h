#pragma once

#include <tuple>
#include <sqt/foundation/statement.h>
#include <sqt/orm/expression/binder/binder_type.h>
#include <sqt/orm/value/identifier/identifier_value_traits_type.h>

namespace sqt {

template<BinderType... BINDER>
class BinderChain;


template<>
class BinderChain<> {
public:
    BinderChain(Statement& statement, std::tuple<>) noexcept { }
};


template<BinderType FIRST, BinderType... REST>
class BinderChain<FIRST, REST...> {
public:
    BinderChain(Statement& statement, std::tuple<FIRST, REST...> binders) :
        statement_(statement),
        binders_(std::move(binders)) {

    }

    auto Bind(const typename FIRST::ValueType& value) {

        const auto& binder = std::get<0>(binders_);
        FIRST::ValueTraits::BindValue(statement_, binder.Index(), value);

        return MakeNextChain();
    }

    template<typename TRAITS = FIRST::ValueTraits>
    auto BindFromEntity(const typename TRAITS::EntityType& entity) const
        requires IdentifierValueTraitsType<TRAITS> {

        const auto& binder = std::get<0>(binders_);
        TRAITS::BindValueFromEntity(statement_, binder.Index(), entity);

        return MakeNextChain();
    }

private:
    auto MakeNextChain() const {

        auto rest_tuple = std::apply([](auto, auto... rest) {
                return std::make_tuple(rest...);
            },
            binders_);

        return BinderChain<REST...>(statement_, std::move(rest_tuple));
    }

private:
    std::tuple<FIRST, REST...> binders_;
    Statement& statement_;
};


template<BinderType... BINDER>
auto MakeBinderChain(Statement& statement, std::tuple<BINDER...> tuple) {
    return BinderChain<BINDER...>(statement, std::move(tuple));
}

}