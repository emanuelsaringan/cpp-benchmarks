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
