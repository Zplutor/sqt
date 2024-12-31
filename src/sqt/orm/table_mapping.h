#pragma once

namespace sqt {

template<typename E>
struct Table;

template<typename E>
using TableT = Table<E>::type;

template<typename E>
constexpr const auto& TableV = TableT<E>::GetInstance();

}