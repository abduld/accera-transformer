
#include "config.hpp"
#include "utils.hpp"

static void BENCHMARK_NAME(CPP_Naive_Memcpy)(benchmark::State& state) {
  aligned_vector<float> Input(N, 1.0 / N), Output(N, 0);
  float output = 0;
  for (auto _ : state) {
    float* inData =
        reinterpret_cast<float*>(__builtin_assume_aligned(Input.data(), XSIMD_DEFAULT_ALIGNMENT));
    float* outData =
        reinterpret_cast<float*>(__builtin_assume_aligned(Output.data(), XSIMD_DEFAULT_ALIGNMENT));

    for (int ii = 0; ii < N; ii++) {
      outData[ii] = inData[ii];
    }
    benchmark::DoNotOptimize(Input.data());
    benchmark::DoNotOptimize(Output.data());
    benchmark::ClobberMemory();
  }
  const int64_t items_processed = state.iterations() * N;
  state.SetItemsProcessed(items_processed);
  state.SetBytesProcessed(items_processed * sizeof(float));
  state.counters["Value"] = N * Output[0]; // Expected to be 1
}

ADD_BENCHMARK(BENCHMARK_NAME(CPP_Naive_Memcpy));

static void BENCHMARK_NAME(CPP_Naive_Memcpy_2)(benchmark::State& state) {
  aligned_vector<float> Input(N, 1.0 / N), Output(N, 0);
  float output = 0;
  for (auto _ : state) {
    float* inData =
        reinterpret_cast<float*>(__builtin_assume_aligned(Input.data(), XSIMD_DEFAULT_ALIGNMENT));
    float* outData =
        reinterpret_cast<float*>(__builtin_assume_aligned(Output.data(), XSIMD_DEFAULT_ALIGNMENT));

    for (int ii = 0; ii < N; ii++) {
      *outData++ = *inData++;
    }
    benchmark::DoNotOptimize(Input.data());
    benchmark::DoNotOptimize(Output.data());
    benchmark::ClobberMemory();
  }
  const int64_t items_processed = state.iterations() * N;
  state.SetItemsProcessed(items_processed);
  state.SetBytesProcessed(items_processed * sizeof(float));
  state.counters["Value"] = N * Output[0]; // Expected to be 1
}

ADD_BENCHMARK(BENCHMARK_NAME(CPP_Naive_Memcpy_2));

static void BENCHMARK_NAME(CPP_Memcpy)(benchmark::State& state) {
  aligned_vector<float> Input(N, 1.0 / N), Output(N, 0);
  float output = 0;
  for (auto _ : state) {
    float* inData =
        reinterpret_cast<float*>(__builtin_assume_aligned(Input.data(), XSIMD_DEFAULT_ALIGNMENT));
    float* outData =
        reinterpret_cast<float*>(__builtin_assume_aligned(Output.data(), XSIMD_DEFAULT_ALIGNMENT));

    std::memcpy(outData, inData, sizeof(float) * N);
    benchmark::DoNotOptimize(Input.data());
    benchmark::DoNotOptimize(Output.data());
    benchmark::ClobberMemory();
  }
  const int64_t items_processed = state.iterations() * N;
  state.SetItemsProcessed(items_processed);
  state.SetBytesProcessed(items_processed * sizeof(float));
  state.counters["Value"] = N * Output[0]; // Expected to be 1
}

ADD_BENCHMARK(BENCHMARK_NAME(CPP_Memcpy));


// static void BENCHMARK_NAME(CPP_Memcpy_Intrinsic)(benchmark::State& state) {
//   aligned_vector<float> Input(N, 1.0 / N), Output(N, 0);
//   float output = 0;
//   for (auto _ : state) {
//     float* inData =
//         reinterpret_cast<float*>(__builtin_assume_aligned(Input.data(), XSIMD_DEFAULT_ALIGNMENT));
//     float* outData =
//         reinterpret_cast<float*>(__builtin_assume_aligned(Output.data(), XSIMD_DEFAULT_ALIGNMENT));

//     __builtin_memcpy_inline(outData, inData, sizeof(float) * N);
//     benchmark::DoNotOptimize(Input.data());
//     benchmark::DoNotOptimize(Output.data());
//     benchmark::ClobberMemory();
//   }
//   const int64_t items_processed = state.iterations() * N;
//   state.SetItemsProcessed(items_processed);
//   state.SetBytesProcessed(items_processed * sizeof(float));
//   state.counters["Value"] = N * Output[0]; // Expected to be 1
// }

// ADD_BENCHMARK(BENCHMARK_NAME(CPP_Memcpy_Intrinsic));