/*
Run on (4 X 3100 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x2)
  L1 Instruction 32 KiB (x2)
  L2 Unified 256 KiB (x2)
  L3 Unified 3072 KiB (x1)
Load Average: 1.43, 0.91, 0.55
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.
---------------------------------------------------------------------
Benchmark                           Time             CPU   Iterations
---------------------------------------------------------------------
BMFixture/TestBinarySearch       10.3 ns         10.3 ns     68900520
BMFixture/TestBsearch            8.00 ns         8.00 ns     88780863
*/

#include <algorithm>
#include <benchmark/benchmark.h>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <numeric>
#include <random>
#include <vector>
#include "benchmark_util.h"

class BMFixture : public benchmark::Fixture {
 public:
  enum : uint16_t { c_size = 100u };
 public:
  BMFixture() : m_nums(c_size) {
    std::iota(m_nums.begin(), m_nums.end(), 0u);
    const std::default_random_engine::result_type t = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(m_nums.begin(), m_nums.end(), std::default_random_engine{t});
    std::sort(m_nums.begin(), m_nums.end());
    m_key = m_nums[std::rand() / ((RAND_MAX + 1u) / m_nums.size())];
  }
 protected:
  std::vector<uint16_t> m_nums;
  uint16_t m_key;
};

BENCHMARK_F(BMFixture, TestBinarySearch)(benchmark::State& state) {
  for (auto _ : state) {
    ASSERT(std::binary_search(m_nums.begin(), m_nums.end(), m_key));
  }
}

BENCHMARK_F(BMFixture, TestBsearch)(benchmark::State& state) {
  assert(m_nums.size() > 0);
  for (auto _ : state) {
    void* result = ::bsearch(
        &m_key, &m_nums[0], m_nums.size(), sizeof(decltype(m_nums)::value_type), util::cmp<uint16_t>);
    ASSERT(*((decltype(m_key)*) result) == m_key);
  }
}

BENCHMARK_MAIN();
