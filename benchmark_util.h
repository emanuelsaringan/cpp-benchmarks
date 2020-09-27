#ifndef _BENCHMARKS_BENCHMARK_UTIL_H_
#define _BENCHMARKS_BENCHMARK_UTIL_H_

#include <cstdint>
#include <cstdlib>

namespace util {

#define LIKELY(x) __builtin_expect(!!(x), 1)
#define UNLIKELY(x) __builtin_expect(!!(x), 0)
#define ASSERT(cond) if (UNLIKELY(not (cond))) { std::abort(); }

template<typename T>
int cmp(const void* a, const void* b) {
  const auto aa = *((T*) a);
  const auto bb = *((T*) b);
  return aa < bb ? -1 : (aa > bb ? 1 : 0);
}

}; // namespace util

#endif // _BENCHMARKS_BENCHMARK_UTIL_H_
