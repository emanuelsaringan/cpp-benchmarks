cmake_minimum_required(VERSION 3.16)
project(benchmarks)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE "Release")

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-march=native" COMPILER_SUPPORTS_MARCH_NATIVE)
if(COMPILER_SUPPORTS_MARCH_NATIVE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
endif()

add_subdirectory("${CMAKE_SOURCE_DIR}/google_benchmark")

add_executable(simd simd.cc)
target_link_libraries(simd benchmark::benchmark)

add_executable(branch_prediction branch_prediction.cc)
target_link_libraries(branch_prediction benchmark::benchmark)

add_executable(atomic atomic.cc)
target_link_libraries(atomic benchmark::benchmark)

add_executable(short_string_optimization short_string_optimization.cc)
target_link_libraries(short_string_optimization benchmark::benchmark)

add_executable(placement_new placement_new.cc)
target_link_libraries(placement_new benchmark::benchmark)

add_executable(vptr vptr.cc)
target_link_libraries(vptr benchmark::benchmark)

add_executable(move move.cc)
target_link_libraries(move benchmark::benchmark)

add_executable(matrix_traversal matrix_traversal.cc)
target_link_libraries(matrix_traversal benchmark::benchmark)

add_executable(buf_iterator buf_iterator.cc)
target_link_libraries(buf_iterator benchmark::benchmark)

add_executable(qsort qsort.cc)
target_link_libraries(qsort benchmark::benchmark)

add_executable(bsearch bsearch.cc)
target_link_libraries(bsearch benchmark::benchmark)

add_executable(crtp crtp.cc)
target_link_libraries(crtp benchmark::benchmark)
