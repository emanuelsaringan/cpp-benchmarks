/*
Run on (4 X 3100 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x2)
  L1 Instruction 32 KiB (x2)
  L2 Unified 256 KiB (x2)
  L3 Unified 3072 KiB (x1)
Load Average: 0.82, 0.90, 0.99
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.
-----------------------------------------------------------------
Benchmark                       Time             CPU   Iterations
-----------------------------------------------------------------
BM_LongStringCreation        19.6 ns         19.6 ns     34516347
BM_ShortStringCreation       1.94 ns         1.94 ns    358449301
BM_LongStringCopy            22.2 ns         22.2 ns     31648372
BM_ShortStringCopy           5.66 ns         5.66 ns    121878825
*/

#include <string>
#include <benchmark/benchmark.h>

static const char* const kLongString = "this is not a short string";
static const char* const kShortString = "a short string";

static void BM_LongStringCreation(benchmark::State& state) {
  for (auto _ : state) {
    const std::string str{kLongString};
    benchmark::DoNotOptimize(str);
  }
}
BENCHMARK(BM_LongStringCreation);

static void BM_ShortStringCreation(benchmark::State& state) {
  for (auto _ : state) {
    const std::string str{kShortString};
    benchmark::DoNotOptimize(str);
  }
}
BENCHMARK(BM_ShortStringCreation);

static void BM_LongStringCopy(benchmark::State& state) {
  const std::string str{kLongString};
  for (auto _ : state) {
    const std::string str_copy{str};
    benchmark::DoNotOptimize(str_copy);
  }
}
BENCHMARK(BM_LongStringCopy);

static void BM_ShortStringCopy(benchmark::State& state) {
  const std::string str{kShortString};
  for (auto _ : state) {
    const std::string str_copy{str};
    benchmark::DoNotOptimize(str_copy);
  }
}
BENCHMARK(BM_ShortStringCopy);

BENCHMARK_MAIN();
