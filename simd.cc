/**
Run on (4 X 3100 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x2)
  L1 Instruction 32 KiB (x2)
  L2 Unified 256 KiB (x2)
  L3 Unified 3072 KiB (x1)
Load Average: 0.59, 0.69, 0.38
***WARNING*** CPU scaling is enabled, the benchmark real time measurements may be noisy and will incur extra overhead.
-------------------------------------------------------------------
Benchmark                         Time             CPU   Iterations
-------------------------------------------------------------------
TestSumFixture/TestBasic       1348 ns         1348 ns       517841
TestSumFixture/TestSIMD        1108 ns         1108 ns       648085
*/

#include <cassert>
#include <cstring>
#include <immintrin.h>

#include <benchmark/benchmark.h>

static constexpr size_t kLen = 4096;

class TestSumFixture : public benchmark::Fixture {
public:
  void SetUp(const benchmark::State&) override {
    for (size_t i = 0; i < kLen; ++i) {
      u_[i] = rand_double();
      v_[i] = rand_double();
    }
  }
  void TearDown(const benchmark::State&) override {
    for (size_t i = 0; i < kLen; ++i) {
      assert(abs(result_[i] - (u_[i] + v_[i])) < 0.000001);
    }
  }
protected:
  double u_[kLen];
  double v_[kLen];
  double result_[kLen];
private:
  double rand_double() const {
    constexpr auto min_val = -256.0;
    constexpr auto max_val = 256.0;
    const auto mult = static_cast<double>(rand()) / RAND_MAX;
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
  constexpr size_t jump = sizeof(__m256d) / sizeof(double);
  for (auto _ : state) {
    for (size_t i = 0; i < kLen; i += jump) {
      const __m256d* uu = reinterpret_cast<__m256d*>(&u_[i]);
      const __m256d* vv = reinterpret_cast<__m256d*>(&v_[i]);
      const __m256d sum = _mm256_add_pd(*uu, *vv);
      *reinterpret_cast<__m256d*>(&result_[i]) = sum;
    }
  }
}

BENCHMARK_MAIN();
