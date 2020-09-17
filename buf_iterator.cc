/*
Run on (4 X 3100 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x2)
  L1 Instruction 32 KiB (x2)
  L2 Unified 256 KiB (x2)
  L3 Unified 3072 KiB (x1)
Load Average: 1.64, 0.85, 0.81
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.
---------------------------------------------------------------
Benchmark                     Time             CPU   Iterations
---------------------------------------------------------------
BMFixture/WithoutBuf     164626 ns       164494 ns         4182
BMFixture/UsingBuf        36303 ns        36280 ns        19300
*/

#include <algorithm>
#include <cstdint>
#include <benchmark/benchmark.h>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

class BMFixture : public benchmark::Fixture {
 public:
  BMFixture() {
    for (uint16_t i = 0u; i < m_size; ++i) {
      m_str += std::to_string(i);
    }
  }
 protected:
  static constexpr uint16_t m_size = 4096u;
  std::string m_str;
};

BENCHMARK_F(BMFixture, WithoutBuf)(benchmark::State& state) {
  for (auto _ : state) {
    std::vector<char> v;
    std::istringstream iss(m_str);
    std::copy(
        std::istream_iterator<char>(iss),
        std::istream_iterator<char>(),
        std::back_inserter(v));
  }
}

BENCHMARK_F(BMFixture, UsingBuf)(benchmark::State& state) {
  for (auto _ : state) {
    std::vector<char> v;
    std::istringstream iss(m_str);
    std::copy(
        std::istreambuf_iterator<char>(iss),
        std::istreambuf_iterator<char>(),
        std::back_inserter(v));
  }
}

BENCHMARK_MAIN();
