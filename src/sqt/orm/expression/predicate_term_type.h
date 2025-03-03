#pragma once

#include <sqt/orm/expression/operand/operand_type.h>
#include <sqt/orm/expression/predicate_type.h>

namespace sqt {

template<typename T>
concept PredicateTermType = OperandType<T> || PredicateType<T>;

}