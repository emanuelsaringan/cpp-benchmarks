/*
Run on (4 X 3100 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x2)
  L1 Instruction 32 KiB (x2)
  L2 Unified 256 KiB (x2)
  L3 Unified 3072 KiB (x1)
Load Average: 1.54, 0.95, 0.85
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.
-------------------------------------------------------------
Benchmark                   Time             CPU   Iterations
-------------------------------------------------------------
BM_TestWithLocking     222006 ns        25422 ns        27379
BM_TestWithAtomic      123530 ns        24972 ns        27972
*/

#include <atomic>
#include <cstdint>
#include <mutex>
#include <thread>
#include <benchmark/benchmark.h>

inline constexpr uint32_t kTarget = 4096u;

uint32_t counter = 0u;
std::mutex mtx;

static void run_with_locking() {
  while (true) {
    std::lock_guard<std::mutex> guard{mtx};
    if (counter == kTarget) {
      return;
    }
    ++counter;
  }
}

static void BM_TestWithLocking(benchmark::State& state) {
  for (auto _ : state) {
    counter = 0u;
    std::thread t1{run_with_locking};
    std::thread t2{run_with_locking};
    t1.join();
    t2.join();
  }
}
BENCHMARK(BM_TestWithLocking);

std::atomic<uint32_t> atomic_counter{0u};

static void run_lock_free() {
  while (atomic_counter.load(std::memory_order_release) < kTarget) {
    atomic_counter.fetch_add(1u, std::memory_order_acquire);
  }
}

static void BM_TestWithAtomic(benchmark::State& state) {
  for (auto _ : state) {
    atomic_counter.store(0u, std::memory_order_acquire);
    std::thread t1{run_lock_free};
    std::thread t2{run_lock_free};
    t1.join();
    t2.join();
  }
}
BENCHMARK(BM_TestWithAtomic);

BENCHMARK_MAIN();
