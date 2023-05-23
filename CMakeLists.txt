# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.15)

project ("LightningScanner" VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

add_library(LightningScanner  "bench/LightningBench.cpp" "include/LightningScanner/LightningScanner.hpp" "include/LightningScanner/backends/Avx2.hpp" "include/LightningScanner/Pattern.hpp" "src/backends/Avx2.cpp" "src/CpuInfo.cpp" "src/backends/Sse42.cpp" "include/LightningScanner/allocator/AlignedAllocator.hpp" "src/backends/Scalar.cpp")

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	set_source_files_properties("src/backends/Avx2.cpp" PROPERTIES COMPILE_FLAGS /arch:AVX2)
elseif ((CMAKE_CXX_COMPILER_ID STREQUAL "Clang") OR (CMAKE_CXX_COMPILER_ID STREQUAL "GNU"))
	set_source_files_properties("src/backends/Avx2.cpp" PROPERTIES COMPILE_FLAGS -mavx2)
	set_source_files_properties("src/backends/Sse42.cpp" PROPERTIES COMPILE_FLAGS -msse4.2)
endif()

target_compile_features(LightningScanner PUBLIC cxx_std_17)
target_include_directories(LightningScanner PUBLIC "${PROJECT_SOURCE_DIR}/include")

option(LIGHTNING_SCANNER_BUILD_BENCH "Build Benchmarks" OFF)
if (LIGHTNING_SCANNER_BUILD_BENCH) 
	add_subdirectory("bench")
endif()

option(LIGHTNING_SCANNER_BUILD_DOCS "Build Docs" OFF)
if (LIGHTNING_SCANNER_BUILD_DOCS)
	add_subdirectory("docs")
endif()

option(LIGHTNING_SCANNER_BUILD_TESTS "Build Tests" OFF)
if (LIGHTNING_SCANNER_BUILD_TESTS )
	add_subdirectory("tests")
endif()