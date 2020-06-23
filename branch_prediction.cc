/**
Run on (4 X 3100 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x2)
  L1 Instruction 32 KiB (x2)
  L2 Unified 256 KiB (x2)
  L3 Unified 3072 KiB (x1)
Load Average: 1.60, 0.55, 0.19
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.
------------------------------------------------------------
Benchmark                  Time             CPU   Iterations
------------------------------------------------------------
BM_TestNoExpect        80657 ns        80614 ns         8158
BM_TestWithExpect      28334 ns        28318 ns        24588
*/

#include <algorithm>
#include <cstdint>
#include <random>
#include <vector>
#include <benchmark/benchmark.h>

#define LIKELY(x) __builtin_expect(!!(x), 1)

static constexpr uint32_t kLen = 16u * 1024u;

static void BM_TestNoExpect(benchmark::State& state) {
  static constexpr uint32_t kNumOnes = kLen / 2;
  std::vector<uint32_t> nums(kLen);
  std::fill_n(nums.begin(), kNumOnes, 1u);
  std::shuffle(nums.begin(), nums.end(), std::default_random_engine{});

  uint32_t num_zeroes = 0u;
  for (auto _ : state) {
    for (auto num : nums) {
      if (num == 0u) {
        benchmark::DoNotOptimize(++num_zeroes);
      }
    }
  }
}
BENCHMARK(BM_TestNoExpect);

static void BM_TestWithExpect(benchmark::State& state) {
  static constexpr uint32_t kNumOnes = kLen / 8;
  std::vector<uint32_t> nums(kLen);
  std::fill_n(nums.begin(), kNumOnes, 1u);
  std::shuffle(nums.begin(), nums.end(), std::default_random_engine{});

  uint32_t num_zeroes = 0u;
  for (auto _ : state) {
    for (auto num : nums) {
      if (LIKELY(num == 0u)) {
        benchmark::DoNotOptimize(++num_zeroes);
      }
    }
  }
}
BENCHMARK(BM_TestWithExpect);

BENCHMARK_MAIN();
