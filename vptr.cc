/*
Run on (4 X 3100 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x2)
  L1 Instruction 32 KiB (x2)
  L2 Unified 256 KiB (x2)
  L3 Unified 3072 KiB (x1)
Load Average: 1.18, 1.23, 1.19
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.
------------------------------------------------------------
Benchmark                  Time             CPU   Iterations
------------------------------------------------------------
BM_VirtualCall       3254442 ns      3254354 ns          211
BM_NonVirtualCall    3245632 ns      3245524 ns          214
*/

#include <cstdint>
#include <benchmark/benchmark.h>

class Base {
 public:
  virtual uint32_t __attribute__((noinline)) foo() const { return 0u; }
};

class Derived : public Base {
 public:
  uint32_t __attribute__((noinline)) foo() const override { return 1u; }
};


namespace {

Derived d;
Base& b = d;

}  // namespace

static void BM_VirtualCall(benchmark::State& state) {
  for (auto _ : state) {
    for (uint32_t i = 0; i < 10'000'000u; ++i) {
      benchmark::DoNotOptimize(b.foo());
    }
  }
}
BENCHMARK(BM_VirtualCall);

static void BM_NonVirtualCall(benchmark::State& state) {
  for (auto _ : state) {
    for (uint32_t i = 0; i < 10'000'000u; ++i) {
      benchmark::DoNotOptimize(d.foo());
    }
  }
}
BENCHMARK(BM_NonVirtualCall);

BENCHMARK_MAIN();