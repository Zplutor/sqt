#pragma once

/**
@file
    Defines the `sqt::BinderChain<>` primary template and its specialization for various numbers of 
    binders.
*/

#include <tuple>
#include <sqt/foundation/statement.h>
#include <sqt/orm/expression/binder/binder_type.h>
#include <sqt/orm/expression/binder/identifier_binder_type.h>

namespace sqt {

/**
The primary template for defining binder chain type for various number of binders.

@tparam BINDER
    The binder types contained in the binder chain. They must satisfy the `sqt::BinderType` 
    concept.

@details
    Binder chains are created by the `sqt::Executor::BeginBindings()` method to bind parameters 
    to placeholders in a querier.

@see sqt::BinderChain<>
@see sqt::BinderChain<FIRST, REST...>
@see sqt::BinderType
@see sqt::Executor<>::BeginBindings()
*/
template<BinderType... BINDER>
class BinderChain;


/**
The specialization for an empty binder chain.

@details
    This specialization is used when no binders are present. It serves as a no-op terminator for
    the binder chain.

@see sqt::BinderChain<FIRST, REST...>
*/
template<>
class BinderChain<> {
public:
    /**
    Constructs an empty binder chain.

    @param statement
        The statement to which values will be bound.

    @param binders
        An empty binder tuple.

    @details
        This constructor exists only for consistency with the other specialization. The parameters 
        are not used.
    */
    BinderChain(Statement& statement, std::tuple<> binders) noexcept { }
};


/**
The specialization for a binder chain with at least one binder.

@tparam FIRST
    The first binder type in the chain.

@tparam REST...
    The remaining binder types in the chain.

@details
    This specialization is used when there is at least one binder in the chain. It provides methods
    to bind a value to the first binder and return a new binder chain for the rest binders, 
    enabling a chain fashion interface.

@see sqt::BinderChain<>
*/
template<BinderType FIRST, BinderType... REST>
class BinderChain<FIRST, REST...> {
public:
    /**
    Constructs a binder chain instance.

    @param statement
        The statement to which values will be bound.

    @param binders
        The binders contained in the chain.

    @details
        The instance stores a reference to the statement. It becomes invalid if the statement is 
        destroyed.
    */
    BinderChain(Statement& statement, std::tuple<FIRST, REST...> binders) noexcept :
        statement_(statement),
        binders_(std::move(binders)) {

    }

    /**
    Binds a value to the first binder in the chain.

    @param value
        The value to bind. Its type is determined by the first binder's value type.

    @return
        A new binder chain instance for the remaining binders.

    @details
        This method uses the information provided by the first binder to bind the specified value 
        to the corresponding placeholder in the statement.

        If the value to bind is from an entity, the `BindFromEntity()` method can also be used for 
        convenience.

    @see sqt::BinderChain<FIRST, REST...>::BindFromEntity()
    @see sqt::BinderType
    */
    auto Bind(const typename FIRST::ValueType& value) const {

        const auto& binder = std::get<0>(binders_);
        FIRST::ValueTraits::BindValue(statement_, binder.Index(), value);

        return MakeNextChain();
    }

    /**
    Binds a value extracted from an entity to the first binder in the chain.

    @param entity
        The entity from which the value will be extracted.

    @return
        A new binder chain instance for the remaining binders.

    @details
        This method is similar to the `Bind()` method, but it binds the value extracted from the
        specified entity. It provides more convenience for binding values directly from entities
        without the need to extract the values manually.

        This method is available only if the first binder satisfies the `sqt::IdentifierBinderType`
        concept.

    @see sqt::BinderChain<FIRST, REST...>::Bind()
    @see sqt::BinderType
    @see sqt::IdentifierBinderType
    */
    template<typename BINDER = FIRST> requires IdentifierBinderType<BINDER>
    auto BindFromEntity(const typename BINDER::ValueTraits::EntityType& entity) const {

        const auto& binder = std::get<0>(binders_);
        BINDER::ValueTraits::BindValueFromEntity(statement_, binder.Index(), entity);

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


/**
A helper function to create a binder chain instance.

@tparam BINDER
    The binder types contained in the binder chain.

@param statement
    The statement to which values will be bound.

@param binders
    The binders contained in the chain.

@return
    A `sqt::BinderChain<>` instance.
*/
template<BinderType... BINDER>
auto MakeBinderChain(Statement& statement, std::tuple<BINDER...> binders) noexcept {
    return BinderChain<BINDER...>(statement, std::move(binders));
}

}