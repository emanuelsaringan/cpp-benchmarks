/*
Run on (4 X 3100 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x2)
  L1 Instruction 32 KiB (x2)
  L2 Unified 256 KiB (x2)
  L3 Unified 3072 KiB (x1)
Load Average: 1.16, 1.39, 1.22
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.
---------------------------------------------------------
Benchmark               Time             CPU   Iterations
---------------------------------------------------------
BMFixture/Copy     250957 ns       250951 ns         2561
BMFixture/Move       1.95 ns         1.95 ns    357850415
*/

#include <string>
#include <vector>
#include <benchmark/benchmark.h>

class BMFixture : public benchmark::Fixture {
public:
  BMFixture() : m_vec(4096, "the quick brown fox jumps over the lazy dog") {}
protected:
  std::vector<std::string> m_vec;
};

BENCHMARK_F(BMFixture, Copy)(benchmark::State& state) {
  for (auto _ : state) {
    const std::vector<std::string> v = m_vec;
    benchmark::DoNotOptimize(v);
  }
}

BENCHMARK_F(BMFixture, Move)(benchmark::State& state) {
  for (auto _ : state) {
    const std::vector<std::string> v = std::move(m_vec);
    benchmark::DoNotOptimize(v);
  }
}

BENCHMARK_MAIN();
