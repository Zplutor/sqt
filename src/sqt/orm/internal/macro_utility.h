#pragma once

#define __SQT_STRINGIZE(X) #X

#define __SQT_JOIN_IMPL_1(A)                      A
#define __SQT_JOIN_IMPL_2(A, B)                   A##_##B
#define __SQT_JOIN_IMPL_3(A, B, C)                A##_##B##_##C
#define __SQT_JOIN_IMPL_4(A, B, C, D)             A##_##B##_##C##_##D
#define __SQT_JOIN_IMPL_5(A, B, C, D, E)          A##_##B##_##C##_##D##_##E
#define __SQT_JOIN_IMPL_6(A, B, C, D, E, F)       A##_##B##_##C##_##D##_##E##_##F
#define __SQT_JOIN_IMPL_7(A, B, C, D, E, F, G)    A##_##B##_##C##_##D##_##E##_##F##_##G
#define __SQT_JOIN_IMPL_8(A, B, C, D, E, F, G, H) A##_##B##_##C##_##D##_##E##_##F##_##G##_##H

#define __SQT_SELECT_JOIN_IMPL(_1, _2, _3, _4, _5, _6, _7, _8, IMPL, ...) IMPL

#define __SQT_JOIN(...) \
__SQT_SELECT_JOIN_IMPL( \
__VA_ARGS__, \
__SQT_JOIN_IMPL_8, \
__SQT_JOIN_IMPL_7, \
__SQT_JOIN_IMPL_6, \
__SQT_JOIN_IMPL_5, \
__SQT_JOIN_IMPL_4, \
__SQT_JOIN_IMPL_3, \
__SQT_JOIN_IMPL_2, \
__SQT_JOIN_IMPL_1 \
)(__VA_ARGS__)
