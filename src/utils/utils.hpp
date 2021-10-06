#pragma once

#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

#include <stdint.h>
#include <string.h>

#include <benchmark/benchmark.h>
#include <xsimd/xsimd.hpp> 

#include "random.hpp"

#ifndef MODULE_NAME
#error "MODULE_NAME is not defined"
#endif // MODULE_NAME

#define PP_STRINGIFY_IMPL(x) #x
#define PP_STRINGIFY(x) PP_STRINGIFY_IMPL(x)

#define MAKE_BENCHMARK_NAME(fn_name) PP_STRINGIFY(MODULE_NAME) "/" PP_STRINGIFY(fn_name)


#define ADD_BENCHMARK(fn) BENCHMARK(fn)->Name(MAKE_BENCHMARK_NAME(fn))->Unit(benchmark::kMillisecond)