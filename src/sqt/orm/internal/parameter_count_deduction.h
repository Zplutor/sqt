#pragma once

#include <sqt/orm/value/entity/entity_value_traits_type.h>
#include <sqt/orm/value/identifier/identifier_value_traits_type.h>
#include <sqt/orm/value/trivial/basic/basic_value_traits_type.h>
#include <sqt/orm/value/trivial/composite/composite_value_traits_type.h>

namespace sqt::internal {

template<typename TRAITS>
class ParameterCountFor;


template<BasicValueTraitsType TRAITS>
class ParameterCountFor<TRAITS> {
public:
    static constexpr std::size_t value = 1;
};


template<CompositeValueTraitsType TRAITS>
class ParameterCountFor<TRAITS> {
public:
    static constexpr std::size_t value = std::tuple_size_v<typename TRAITS::ValueType>;
};


template<IdentifierValueTraitsType TRAITS>
class ParameterCountFor<TRAITS> {
public:
    static constexpr std::size_t value = 
        ParameterCountFor<typename TRAITS::IdentifierType::ValueTraits>::value;
};


template<EntityValueTraitsType TRAITS>
class ParameterCountFor<TRAITS> {
public:
    static constexpr std::size_t value = TRAITS::ManipulatingColumns.size();
};


template<typename TRAITS>
constexpr std::size_t ParameterCountForV = ParameterCountFor<TRAITS>::value;

}