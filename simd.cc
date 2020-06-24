/**
Run on (4 X 3100 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x2)
  L1 Instruction 32 KiB (x2)
  L2 Unified 256 KiB (x2)
  L3 Unified 3072 KiB (x1)
Load Average: 0.85, 0.85, 0.56
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.
-------------------------------------------------------------------
Benchmark                         Time             CPU   Iterations
-------------------------------------------------------------------
TestSumFixture/TestBasic        719 ns          718 ns       908860
TestSumFixture/TestSIMD         551 ns          551 ns      1346390
*/

#include <cassert>
#include <cstring>
#include <exception>
#include <iostream>
#include <immintrin.h>
#include <benchmark/benchmark.h>

#define ASSERT(cond) if (not (cond)) { std::cerr << "Assertion error at line: " << __LINE__ << std::endl; std::terminate(); }

static constexpr size_t kLen = 4096;

class TestSumFixture : public benchmark::Fixture {
public:
  void SetUp(const benchmark::State&) override {
    for (size_t i = 0; i < kLen; ++i) {
      u_[i] = rand_float();
      v_[i] = rand_float();
    }
  }
  void TearDown(const benchmark::State&) override {
    for (size_t i = 0; i < kLen; ++i) {
      ASSERT(abs(result_[i] - (u_[i] + v_[i])) < 0.000001);
    }
  }
protected:
  float u_[kLen];
  float v_[kLen];
  float result_[kLen];
private:
  float rand_float() const {
    constexpr auto min_val = -256.0f;
    constexpr auto max_val = 256.0f;
    const auto mult = static_cast<float>(rand()) / RAND_MAX;
    return min_val + mult * (max_val - min_val);
  }
};

BENCHMARK_F(TestSumFixture, TestBasic)(benchmark::State& state) {
  for (auto _ : state) {
    for (size_t i = 0; i < kLen; ++i) {
      result_[i] = u_[i] + v_[i];
    }
  }
}

BENCHMARK_F(TestSumFixture, TestSIMD)(benchmark::State& state) {
  constexpr size_t jump = sizeof(__m256) / sizeof(float);
  for (auto _ : state) {
    for (size_t i = 0; i < kLen; i += jump) {
      const __m256* uu = reinterpret_cast<__m256*>(&u_[i]);
      const __m256* vv = reinterpret_cast<__m256*>(&v_[i]);
      *reinterpret_cast<__m256*>(&result_[i]) = _mm256_add_ps(*uu, *vv);
    }
  }
}

BENCHMARK_MAIN();
