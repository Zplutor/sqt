#pragma once

#include <sqt/orm/querier/querier_like.h>

namespace sqt {

template<typename T>
concept SelecterLike = QuerierLike<T> && requires(Statement& statement) {
    typename T::ResultElementType;
    { T::GetResultElement(statement) } -> std::same_as<typename T::ResultElementType>;
};

}