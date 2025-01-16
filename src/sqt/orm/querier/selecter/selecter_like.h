#pragma once

#include <sqt/orm/querier/querier_like.h>

namespace sqt {

template<typename T>
concept SelecterLike = QuerierLike<T>;

}