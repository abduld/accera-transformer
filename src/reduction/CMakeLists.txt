set(MODULE_NAME reduction)

add_executable(${MODULE_NAME}
  main.cpp
  memcpy.cpp
  cpp_naive.cpp 
  cpp_simd_openmp.cpp
  cpp_simd_xsimd.cpp 
)
add_accera(${MODULE_NAME} naive vectorized)

target_compile_definitions(${MODULE_NAME} PRIVATE -DMODULE_NAME=${MODULE_NAME})
target_include_directories(${MODULE_NAME} SYSTEM PRIVATE
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
)


set_target_properties(${MODULE_NAME}
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

