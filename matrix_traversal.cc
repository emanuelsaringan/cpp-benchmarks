/*
Run on (4 X 3100 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x2)
  L1 Instruction 32 KiB (x2)
  L2 Unified 256 KiB (x2)
  L3 Unified 3072 KiB (x1)
Load Average: 1.27, 1.55, 1.21
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.
---------------------------------------------------------
Benchmark               Time             CPU   Iterations
---------------------------------------------------------
BM_RowOrder      13227526 ns     13222523 ns           52
BM_ColumnOrder  537882944 ns    537557224 ns            2
*/

#include <cstdint>
#include <benchmark/benchmark.h>

inline constexpr uint32_t kLen = 4096u;
uint64_t arr[kLen][kLen];

static void BM_RowOrder(benchmark::State& state) {
  for (auto _ : state) {
    for (size_t i = 0; i < kLen; ++i) {
      for (size_t j = 0; j < kLen; ++j) {
        benchmark::DoNotOptimize(arr[i][j]);
      }
    }
  }
}
BENCHMARK(BM_RowOrder);

static void BM_ColumnOrder(benchmark::State& state) {
  for (auto _ : state) {
    for (size_t j = 0; j < kLen; ++j) {
      for (size_t i = 0; i < kLen; ++i) {
        benchmark::DoNotOptimize(arr[i][j]);
      }
    }
  }
}
BENCHMARK(BM_ColumnOrder);

BENCHMARK_MAIN();
