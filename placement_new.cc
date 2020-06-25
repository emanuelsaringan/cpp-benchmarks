/*
Run on (4 X 3100 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x2)
  L1 Instruction 32 KiB (x2)
  L2 Unified 256 KiB (x2)
  L3 Unified 3072 KiB (x1)
Load Average: 1.22, 1.13, 1.06
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.
---------------------------------------------------------------
Benchmark                     Time             CPU   Iterations
---------------------------------------------------------------
BM_New<Foo>                19.2 ns         18.8 ns     29289050
BM_PlacementNew<Foo>      0.329 ns        0.329 ns   1000000000
*/

#include <cstdint>
#include <string>
#include <benchmark/benchmark.h>

struct Foo {
  uint64_t m0;
  uint64_t m1;
  uint64_t m2;
  uint64_t m3;
  uint64_t m4;
  uint64_t m5;
  uint64_t m6;
  uint64_t m7;
  uint64_t m8;
  uint64_t m9;
  uint64_t m10;
  uint64_t m11;
  uint64_t m12;
  uint64_t m13;
  uint64_t m14;
  uint64_t m15;
  uint64_t m16;
  uint64_t m17;
  uint64_t m18;
  uint64_t m19;
};

template<typename T>
static void BM_New(benchmark::State& state) {
  for (auto _ : state) {
    auto* t = new T;
    benchmark::DoNotOptimize(t);
    delete t;
  }
}
BENCHMARK_TEMPLATE(BM_New, Foo);

template<typename T>
static void BM_PlacementNew(benchmark::State& state) {
  char* buf = new char[sizeof(T)];
  for (auto _ : state) {
    auto* t = new (buf) T;
    benchmark::DoNotOptimize(t);
    t->~T();
  }
  delete[] buf;
}
BENCHMARK_TEMPLATE(BM_PlacementNew, Foo);

BENCHMARK_MAIN();