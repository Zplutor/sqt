#pragma once

#include <string>
#include <sqt/orm/column/abstract_column.h>

namespace sqt {

std::string JoinColumnNames(AbstractColumnsView columns);

std::string JoinPlaceholders(std::size_t count);

}