#include "config.hpp"
#include "utils.hpp"

static void CPP_SIMD_OpenMP(benchmark::State& state) {
  std::vector<float, xsimd::aligned_allocator<float, XSIMD_DEFAULT_ALIGNMENT>> in(BATCH_SIZE * N,
                                                                                  1),
      out(BATCH_SIZE * N);
  for (auto _ : state) {
    for (int ii = 0; ii < BATCH_SIZE; ii++) {
      const auto inData  = in.data() + ii * N;
      auto outData       = out.data() + ii * N;
      auto maxVal        = -std::numeric_limits<float>::max();
#pragma omp simd reduction(max : maxVal) aligned(inData : XSIMD_DEFAULT_ALIGNMENT)
      for (int idx = 0; idx < N; idx++) {
        maxVal = std::max(maxVal, inData[idx]);
      }
      float sum = 0;
#pragma omp simd reduction(+ : sum) aligned(inData, outData : XSIMD_DEFAULT_ALIGNMENT)
      for (int idx = 0; idx < N; idx++) {
        outData[idx] = std::exp(inData[idx] - maxVal);
        sum += outData[idx];
      }
#pragma omp simd aligned(outData : 32)
      for (int idx = 0; idx < N; idx++) {
        outData[idx] /= sum;
      }
    }
    benchmark::DoNotOptimize(out.data());
    benchmark::ClobberMemory();
  }
  const int64_t items_processed = state.iterations() * N * BATCH_SIZE;
  state.SetItemsProcessed(items_processed);
  state.SetBytesProcessed(items_processed * sizeof(float));
  state.counters["Value"] = N * out[0]; // Expected to be 1
}

ADD_BENCHMARK(CPP_SIMD_OpenMP);