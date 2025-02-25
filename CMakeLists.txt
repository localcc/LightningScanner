# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required(VERSION 3.15)

project("LightningScanner" VERSION 1.0.1 LANGUAGES CXX)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

include(GNUInstallDirs)

set(LIGHTNING_SCANNER_INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_INCLUDEDIR}")
set(LIGHTNING_SCANNER_LIBRARY_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}")
set(LIGHTNING_SCANNER_BINARY_INSTALL_DIR "${CMAKE_INSTALL_BINDIR}")
set(LIGHTNING_SCANNER_CONFIG_INSTALL_DIR "${CMAKE_INSTALL_DATADIR}/cmake/LightningScanner" CACHE INTERNAL "")

if (MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif ()

add_library(LightningScanner "include/LightningScanner/LightningScanner.hpp"
        "include/LightningScanner/Pattern.hpp"
        "src/CpuInfo.cpp"
        "include/LightningScanner/allocator/AlignedAllocator.hpp"
        "src/backends/Scalar.cpp"
        "src/backends/StdFind.cpp")

if (NOT CMAKE_SYSTEM_PROCESSOR STREQUAL "arm64")
    target_sources(LightningScanner PRIVATE
            "src/backends/Avx2.cpp"
            "src/backends/Sse42.cpp"
    )

    if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        set_source_files_properties("src/backends/Avx2.cpp" PROPERTIES COMPILE_FLAGS /arch:AVX2)
    else ()
        set_source_files_properties("src/backends/Avx2.cpp" PROPERTIES COMPILE_FLAGS -mavx2)
        set_source_files_properties("src/backends/Sse42.cpp" PROPERTIES COMPILE_FLAGS -msse4.2)
    endif ()
endif ()

target_compile_features(LightningScanner PUBLIC cxx_std_17)
target_include_directories(LightningScanner PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${LIGHTNING_SCANNER_INCLUDE_INSTALL_DIR}>)

option(LIGHTNING_SCANNER_BUILD_BENCH "Build Benchmarks" OFF)
if (LIGHTNING_SCANNER_BUILD_BENCH)
    add_subdirectory("bench")
endif ()

option(LIGHTNING_SCANNER_BUILD_DOCS "Build Docs" OFF)
if (LIGHTNING_SCANNER_BUILD_DOCS)
    add_subdirectory("docs")
endif ()

option(LIGHTNING_SCANNER_BUILD_TESTS "Build Tests" OFF)
if (LIGHTNING_SCANNER_BUILD_TESTS)
    add_subdirectory("tests")
endif ()

## Install 
if (LIGHTNING_SCANNER_INSTALL)
    include(CMakePackageConfigHelpers)

    install(
            DIRECTORY "${PROJECT_SOURCE_DIR}/include/LightningScanner"
            DESTINATION "${LIGHTNING_SCANNER_INCLUDE_INSTALL_DIR}"
    )
    install(
            TARGETS LightningScanner
            EXPORT LightningScannerTargets
            INCLUDES DESTINATION "${LIGHTNING_SCANNER_INCLUDE_INSTALL_DIR}"
            LIBRARY DESTINATION "${LIGHTNING_SCANNER_LIBRARY_INSTALL_DIR}"
            ARCHIVE DESTINATION "${LIGHTNING_SCANNER_LIBRARY_INSTALL_DIR}"
            RUNTIME DESTINATION "${LIGHTNING_SCANNER_BINARY_INSTALL_DIR}"
    )
    export(
            TARGETS LightningScanner
            NAMESPACE LightningScanner::
            FILE "${LIGHTNING_SCANNER_CONFIG_INSTALL_DIR}/LightningScannerTargets.cmake"
    )

    write_basic_package_version_file(
            "LightningScannerVersion.cmake"
            COMPATIBILITY AnyNewerVersion
    )
    install(
            FILES "${CMAKE_CURRENT_BINARY_DIR}/LightningScannerVersion.cmake" "cmake/LightningScannerConfig.cmake"
            DESTINATION "${LIGHTNING_SCANNER_CONFIG_INSTALL_DIR}"
    )
    install(
            EXPORT LightningScannerTargets
            NAMESPACE LightningScanner::
            DESTINATION "${LIGHTNING_SCANNER_CONFIG_INSTALL_DIR}"
    )

endif ()