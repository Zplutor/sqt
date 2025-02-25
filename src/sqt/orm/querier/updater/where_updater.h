#pragma once

#include <sqt/orm/querier/where_querier.h>

namespace sqt {

template<QuerierType UPDATER, ExpressionLike EXPRESSION>
class WhereUpdater : public WhereQuerier<UPDATER, EXPRESSION> {

};

}