#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdint.h>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <assert.h>
#include <sys/resource.h>

extern const char *argv0;

#define MAX_PROFILE_EVENTS 2

#define _XSTR(x) #x
#define XSTR(x) _XSTR(x)

#define PLINE(...) \
    (printf(XSTR(__FILE__) ":" XSTR(__LINE__) ":\n" __VA_ARGS__), fflush(stdout))

#define TIMED_BEGIN { u64 __start = measure_time_now_ms();
#define TIMED_END(name) PLINE(XSTR(name) ": %lums\n", measure_time_now_ms() - __start); }

#define likely(x)   (__builtin_expect(!!(x), 1))
#define unlikely(x) (__builtin_expect(!!(x), 0))

#define MIN(a, b) ((a) <= (b) ? (a) : (b))
#define MAX(a, b) ((a) >= (b) ? (a) : (b))

#define ALIGN(x, align)         ((__typeof(x))((((u64)(x)) + (((u64)align) - 1ULL)) & ~(((u64)align) - 1ULL)))
#define IS_ALIGNED(x, align)    (!(((u64)(x)) & (((u64)align) - 1ULL)))
#define IS_ALIGNED_PP(x, align) (!((x) & ((align) - 1ULL)))
#define IS_POWER_OF_TWO(x)      ((x) != 0 && IS_ALIGNED((x), (x)))
#define IS_POWER_OF_TWO_PP(x)   ((x) != 0 && IS_ALIGNED_PP((x), (x)))

#define UINT(w) uint##w##_t
#define SINT(w) int##w##_t

#define u8  UINT(8 )
#define u16 UINT(16)
#define u32 UINT(32)
#define u64 UINT(64)

#define i8  SINT(8 )
#define i16 SINT(16)
#define i32 SINT(32)
#define i64 SINT(64)

#define KB(x)    (x*(1ull<<10))
#define MB(x)    (x*(1ull<<20))
#define GB(x)    (x*(1ull<<30))
#define TB(x)    (x*(1ull<<40))
#define TO_KB(x) (x/(1ull<<10))
#define TO_MB(x) (x/(1ull<<20))
#define TO_GB(x) (x/(1ull<<30))
#define TO_TB(x) (x/(1ull<<40))

#define PAGE_SHIFT (12ULL)
#define PAGE_SIZE  (1ULL << PAGE_SHIFT)

typedef void *addr_t;

#define UTIL_FN_PRELUDE static __inline__

UTIL_FN_PRELUDE
u64 next_power_of_2(u64 x) {
    if (x == 0) {
        return 2;
    }

    x--;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    x |= x >> 32;
    x++;

    return x;
}

UTIL_FN_PRELUDE
u64 measure_time_now_ns(void) {
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC, &ts);

    return (1000000000ULL * ts.tv_sec) + ts.tv_nsec;
}

UTIL_FN_PRELUDE
u64 measure_time_now_us(void) {
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC, &ts);

    return (1000000ULL * ts.tv_sec) + (ts.tv_nsec / 1000ULL);
}

UTIL_FN_PRELUDE
u64 measure_time_now_ms(void) {
    struct timespec ts;

    clock_gettime(CLOCK_MONOTONIC, &ts);

    return (10000ULL * ts.tv_sec) + (ts.tv_nsec / 1000000ULL);
}

UTIL_FN_PRELUDE
u64 sum_u64_array(u64 *x, int len) {
    int i;
    u64 sum;

    sum = 0;
    for ( i = 0; i < len; i++) {
        sum += x[i];
    }
    return sum;
}

UTIL_FN_PRELUDE
float sum_float_array(float *x, int len) {
    int i;
    float sum;

    sum = 0.0;
    for ( i = 0; i < len; i++) {
        sum += x[i];
    }
    return sum;
}


#define ERR(_fmt, ...)                                    \
do {                                                      \
    int _save_errno = errno;                              \
    fprintf(stderr, "%sERROR\e[00m: " _fmt,               \
            isatty(2) ? "\e[0;31m" : "", ##__VA_ARGS__);  \
    if (_save_errno) { exit(_save_errno); }               \
    exit(1);                                              \
} while (0)

#define ERR_NOEXIT(_fmt, ...)                             \
do {                                                      \
    fprintf(stderr, "%sERROR\e[00m: " _fmt,               \
            isatty(2) ? "\e[0;31m" : "", ##__VA_ARGS__);  \
} while (0)

#define WARN(_fmt, ...)                                   \
do {                                                      \
    fprintf(stderr, "%sWARN\e[00m:  " _fmt,               \
            isatty(2) ? "\e[0;33m" : "", ##__VA_ARGS__);  \
} while (0)

#define INFO(_fmt, ...)                                   \
do {                                                      \
    fprintf(stderr, "%sINFO\e[00m:  " _fmt,               \
            isatty(2) ? "\e[0;36m" : "", ##__VA_ARGS__);  \
} while (0)


UTIL_FN_PRELUDE
u64 safe_diff(u64 x, u64 y) {
    return ((x > y) ? (x - y) : ((u64)0));
}

UTIL_FN_PRELUDE
float pages_to_MB(u64 pages) {
    return ( (float)(pages << PAGE_SHIFT) / (1024.0*1024.0) );
}

UTIL_FN_PRELUDE
int bump_nofile_rlimit(void) {
    int status;
	struct rlimit rlim_new = {
		.rlim_cur	= 16384,
		.rlim_max	= 16384,
	};

    status = setrlimit(RLIMIT_NOFILE, &rlim_new);

    if (status != 0) {
        WARN("failed to increase file limit (errno = %d)\n", errno);
    }

    return status;
}
static __inline__ unsigned long long rdtsc(void)
{
    unsigned hi, lo;
    asm volatile ("rdtsc" : "=a"(lo), "=d"(hi));
    return ( (unsigned long long)lo)|( ((unsigned long long)hi)<<32 );
}

#endif
