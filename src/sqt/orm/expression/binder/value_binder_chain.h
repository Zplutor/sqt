#pragma once

#include <tuple>
#include <sqt/foundation/statement.h>
#include <sqt/orm/expression/binder/value_binder_type.h>
#include <sqt/orm/value/traits/identifier_value_traits_type.h>

namespace sqt {

template<ValueBinderType... BINDER>
class ValueBinderChain;


template<>
class ValueBinderChain<> {
public:
    ValueBinderChain(Statement& statement, std::tuple<>) noexcept { }
};


template<ValueBinderType FIRST, ValueBinderType... REST>
class ValueBinderChain<FIRST, REST...> {
public:
    ValueBinderChain(Statement& statement, std::tuple<FIRST, REST...> binders) :
        statement_(statement),
        binders_(std::move(binders)) {

    }

    auto Bind(const typename FIRST::ValueType& value) {

        const auto& binder = std::get<0>(binders_);
        FIRST::ValueTraits::BindValue(statement_, binder.GetIndex(), value);

        return MakeNextChain();
    }

    template<typename TRAITS = FIRST::ValueTraits>
    auto BindFromEntity(const typename TRAITS::EntityType& entity) const
        requires IdentifierValueTraitsType<TRAITS> {

        const auto& binder = std::get<0>(binders_);
        TRAITS::BindValueFromEntity(statement_, binder.GetIndex(), entity);

        return MakeNextChain();
    }

private:
    auto MakeNextChain() const {

        auto rest_tuple = std::apply([](auto, auto... rest) {
                return std::make_tuple(rest...);
            },
            binders_);

        return ValueBinderChain<REST...>(statement_, std::move(rest_tuple));
    }

private:
    std::tuple<FIRST, REST...> binders_;
    Statement& statement_;
};


template<ValueBinderType... BINDER>
auto MakeBinderChain(Statement& statement, std::tuple<BINDER...> tuple) {
    return ValueBinderChain<BINDER...>(statement, std::move(tuple));
}


template<typename T>
concept BinderLikeTuple = requires(T t, Statement & statement) {
    MakeBinderChain(statement, t);
};

}