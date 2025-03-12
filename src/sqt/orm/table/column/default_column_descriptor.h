#pragma once

#include <sqt/orm/value/nullable_value_type.h>
#include <sqt/orm/value/primitive_value_type.h>
#include <sqt/orm/value/traits/trivial_value_traits.h>

namespace sqt {

template<typename VALUE>
class DefaultColumnDescriptor;


template<PrimitiveValueType VALUE>
class DefaultColumnDescriptor<VALUE> {
public:
    using ValueTraits = TrivialValueTraits<VALUE>;

    static constexpr sqt::DataType DataType = MapToDataTypeV<VALUE>;
    static constexpr bool IsNullable = false;
};


template<NullableValueType VALUE>
class DefaultColumnDescriptor<VALUE> {
public:
    using ValueTraits = TrivialValueTraits<VALUE>;

    static constexpr sqt::DataType DataType = MapToDataTypeV<GetOptionalValueTypeT<VALUE>>;
    static constexpr bool IsNullable = true;
};

}