#pragma once

#define __SQL_UTILITY_EXPAND(X) X

#define __SQL_UTILITY_JOIN_(A, B, C, D, E, F, G, H, ...) A##B##C##D##E##F##G##H

#define __SQL_UTILITY_JOIN(...) __SQL_UTILITY_EXPAND( __SQL_UTILITY_JOIN_(__VA_ARGS__,,,,,,,) )

#define __SQT_UTILITY_STRINGIZE(X) #X