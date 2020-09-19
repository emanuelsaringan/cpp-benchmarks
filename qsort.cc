/*
Run on (4 X 3100 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x2)
  L1 Instruction 32 KiB (x2)
  L2 Unified 256 KiB (x2)
  L3 Unified 3072 KiB (x1)
Load Average: 1.31, 1.38, 1.58
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.
--------------------------------------------------------------
Benchmark                    Time             CPU   Iterations
--------------------------------------------------------------
BMFixture/TestSort         436 ns          436 ns      1599477
BMFixture/TestQsort       2725 ns         2719 ns       260899
*/

#include <algorithm>
#include <benchmark/benchmark.h>
#include <cstdint>
#include <iostream>
#include <random>
#include <vector>
#include <stdlib.h>

class BMFixture : public benchmark::Fixture {
 public:
  enum : uint16_t {
    c_size = 100u
  };
 public:
  BMFixture() : m_nums(c_size) {
    std::iota(m_nums.begin(), m_nums.end(), 0u);
    std::shuffle(m_nums.begin(), m_nums.end(), std::default_random_engine{});
  }
 protected:
  std::vector<uint16_t> m_nums;
};

BENCHMARK_F(BMFixture, TestSort)(benchmark::State& state) {
  for (auto _ : state) {
    std::sort(m_nums.begin(), m_nums.end());
  }
}

int uint16_cmp(const void* a, const void* b) {
  auto aa = *(uint16_t*)a;
  auto bb = *(uint16_t*)b;
  if (aa < bb) {
    return -1;
  } else if (aa > bb) {
    return 1;
  }
  return 0;
}

BENCHMARK_F(BMFixture, TestQsort)(benchmark::State& state) {
  for (auto _ : state) {
    ::qsort(&m_nums[0], m_nums.size(), sizeof(decltype(m_nums)::value_type), uint16_cmp);
  }
}

BENCHMARK_MAIN();
