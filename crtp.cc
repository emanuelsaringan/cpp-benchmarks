/**
Run on (4 X 3100 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x2)
  L1 Instruction 32 KiB (x2)
  L2 Unified 256 KiB (x2)
  L3 Unified 3072 KiB (x1)
Load Average: 1.07, 1.22, 1.28
-----------------------------------------------------
Benchmark           Time             CPU   Iterations
-----------------------------------------------------
BM_vptr         0.982 ns        0.981 ns    720051897
BM_crtp         0.332 ns        0.332 ns   1000000000
*/

#include <cstdint>
#include <memory>
#include <benchmark/benchmark.h>

class Animal {
 public:
  virtual uint16_t type_id() const = 0;
};

class Dog : public Animal {
 public:
  uint16_t type_id() const override { return 1u; }
};

template <typename T>
class AnimalCRTP {
 public:
  uint16_t type_id() const {
    return static_cast<const T*>(this)->type_id();
  }
};

class DogCRTP : public AnimalCRTP<DogCRTP> {
 public:
  uint16_t type_id() const { return 2u; }
};

std::unique_ptr<Animal> animal_ptr(new Dog);
AnimalCRTP<DogCRTP> animal_crtp;

static void BM_vptr(benchmark::State& state) {
  Animal* animal = animal_ptr.get();
  for (auto _ : state) {
    benchmark::DoNotOptimize(animal->type_id());
  }
}
BENCHMARK(BM_vptr);

static void BM_crtp(benchmark::State& state) {
  for (auto _ : state) {
    benchmark::DoNotOptimize(animal_crtp.type_id());
  }
}
BENCHMARK(BM_crtp);

BENCHMARK_MAIN();
