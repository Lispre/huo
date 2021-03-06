#ifndef HUO_CONFIG_H
#define HUO_CONFIG_H 1

#include <stddef.h>
#include <stdint.h>

#define PRIhi PRId64
#define PRIuhi PRIu64

#define SCNhi SCNd64
#define SCNuhi SCNu64

typedef int64_t huo_int_t;
typedef uint64_t huo_uint_t;
typedef uint_fast16_t huo_depth_t;

#if 0
#define malloc(x) _check_malloc(x)
#endif

#if defined(__clang__)
// Clang defines __gnuc__ ???
#define __UINT128__ unsigned __int128

#if __has_builtin(__builtin_mul_overflow)
#define MUL_OVERFLOW(a, b, res) __builtin_mul_overflow((a), (b), (res))
#elif __has_builtin(__builtin_umulll_overflow) && SIZE_MAX == ULLONG_MAX
#define MUL_OVERFLOW(a, b, res) __builtin_umulll_overflow((unsigned long long) (a), (unsigned long long) (b), (unsigned long long *) (res))
#elif __has_builtin(__builtin_umull_overflow) && SIZE_MAX == ULONG_MAX
#define MUL_OVERFLOW(a, b, res) __builtin_umull_overflow((unsigned long) (a), (unsigned long) (b), (unsigned long *) (res))
#elif __has_builtin(__builtin_umul_overflow) && SIZE_MAX == UINT_MAX
#define MUL_OVERFLOW(a, b, res) __builtin_umul_overflow((unsigned int) (a), (unsigned int) (b), (unsigned int *) (res))
#endif

#define HAS_STATIC_ASSERT __has_extension(c_static_assert)

#elif defined(__GNUC__)

#define __UINT128__ unsigned __int128

#define MUL_OVERFLOW(a, b, res) __builtin_mul_overflow((a), (b), (res))

#define HAS_STATIC_ASSERT 1

#endif



#if HAS_STATIC_ASSERT

#define STATIC_ASSERT(cond,msg) CTA2(cond, msg)
#define CTA2(cond, msg) _Static_assert(cond,msg)

#else

#pragma message "Using fallback static assert"

#define CTASTR2(pre,post) pre ## post
#define CTASTR(pre,post) CTASTR2(pre,post)
#define STATIC_ASSERT(cond,msg) \
    typedef struct { int CTASTR(static_assertion_failed_,msg) : !!(cond); } \
        CTASTR(static_assertion_failed_,__COUNTER__)

#endif

void *_check_malloc(size_t s);

#endif
