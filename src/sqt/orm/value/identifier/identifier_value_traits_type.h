#pragma once

#include <sqt/orm/value/value_traits_type.h>

namespace sqt {

template<typename T>
concept IdentifierValueTraitsType = ValueTraitsType<T> && requires {
    typename T::IdentifierType;
    typename T::EntityType;
};

}