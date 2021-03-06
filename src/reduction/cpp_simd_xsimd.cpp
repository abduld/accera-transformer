
#include "config.hpp"

namespace xs = xsimd;

static void BENCHMARK_NAME(CPP_XSIMD)(benchmark::State &state) {
  aligned_vector<float> Input(N, 1.0 / N);
  float output = 0;
  for (auto _ : state) {
    float *inData = reinterpret_cast<float *>(
        __builtin_assume_aligned(Input.data(), XSIMD_DEFAULT_ALIGNMENT));
    /// [reduce]
    output = xsimd::reduce(inData, inData + N, 0.0f);
    /// [reduce]
    benchmark::DoNotOptimize(inData);
    benchmark::ClobberMemory();
  }

  const int64_t items_processed = state.iterations() * N;
  state.SetItemsProcessed(items_processed);
  state.SetBytesProcessed(items_processed * sizeof(float));
  state.counters["Value"] = output; // Expected to be 1
}

ADD_BENCHMARK(BENCHMARK_NAME(CPP_XSIMD));