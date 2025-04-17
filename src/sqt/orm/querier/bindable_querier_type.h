#pragma once

/**
@file
    Defines the `sqt::BindableQuerierType` concept.
*/

#include <sqt/orm/querier/querier_type.h>

namespace sqt {

/**
Constraints a type to be an querier type, which has bindable placeholders.

@details
    @b Requirements
    - The type must satisfy the `sqt::QuerierType` concept.
    - The static method `BuildPlaceholderBinders()` must return a non-empty tuple of binders, 
      indicating that the querier has bindable placeholders.

@see sqt::QuerierType
*/
template<typename T>
concept BindableQuerierType = QuerierType<T> && requires {
    requires std::tuple_size_v<decltype(T::BuildPlaceholderBinders())> > 0;
};

}
