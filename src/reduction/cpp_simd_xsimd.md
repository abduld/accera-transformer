---
benchmark_name: CPP_XSIMD
cpp_code: src/reduction/cpp_simd_xsimd.cpp
---
# Vectorized C++ Using XSIMD

> [!Note]
> The following shows the implementation of the `{{benchmark_name}}` baseline.
> The full source code listing is found in [{{cpp_code}} :fas fa-code: ]({{cpp_code}}). 

We implement a vectorized reductions in C++ by leveraging the [XSIMD](https://github.com/xtensor-stack/xsimd) library.



[](cpp_simd_xsimd.cpp ':include :type=code cpp :fragment=reduce')
 