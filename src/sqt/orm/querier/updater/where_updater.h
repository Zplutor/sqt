#pragma once

#include <sqt/orm/querier/where_querier.h>

namespace sqt {

template<QuerierLike UPDATER, ExpressionLike EXPRESSION>
class WhereUpdater : public WhereQuerier<UPDATER, EXPRESSION> {

};

}