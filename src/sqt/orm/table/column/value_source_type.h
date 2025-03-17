#pragma once

#include <concepts>

namespace sqt {

template<typename T, typename ENTITY>
concept ValueSourceType = 
    requires {
        typename T::ValueType;
    } &&
    requires (const ENTITY& entity) {
        { T::GetValueFromEntity(entity) } -> std::convertible_to<const typename T::ValueType&>;
    } &&
    requires (ENTITY& entity, typename T::ValueType&& value) {
        { T::SetValueToEntity(entity, std::move(value)) } -> std::same_as<void>;
    };

}