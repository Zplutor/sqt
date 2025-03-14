#pragma once

#include <concepts>
#include <sqt/orm/value/value_traits_type.h>

namespace sqt {

template<typename T>
concept IdentifierDescriptorType = 
    requires {
        typename T::EntityType;
        typename T::ValueTraits;
    } &&
    ValueTraitsType<typename T::ValueTraits> &&
    requires(const typename T::EntityType& entity) {
        { T::GetValueFromEntity(entity) } ->
            std::convertible_to<const typename T::ValueTraits::ValueType&>;
    }&&
    requires(typename T::EntityType& entity, typename T::ValueTraits::ValueType&& value) {
        { T::SetValueToEntity(entity, std::move(value)) } -> std::same_as<void>;
    };

}