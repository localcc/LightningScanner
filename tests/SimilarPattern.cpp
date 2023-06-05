#include <LightningScanner/CpuInfo.hpp>
#include <LightningScanner/LightningScanner.hpp>

#include <gtest/gtest.h>

/**
 * Check that similar patterns scan correctly
 */

using namespace LightningScanner;

static constexpr uint8_t dataSet[] = {
    0x40, 0x57, 0x48, 0x83, 0xEC, 0x30, 0x48, 0xC7, 0x44, 0x24, 0x28, 0xFE,
    0xFF, 0xFF, 0xFF, 0x48, 0x89, 0x5C, 0x24, 0x40, 0x48, 0x89, 0x6C, 0x24,
    0x48, 0x48, 0x89, 0x74, 0x24, 0x50, 0x49, 0x8B, 0xE9, 0x49, 0x8B, 0xF0,
    0x40, 0x57, 0x48, 0x83, 0xEC, 0x30, 0x48, 0xC7, 0x44, 0x24, 0x28, 0xFE,
    0xFF, 0xFF, 0xFF, 0x48, 0x89, 0x5C, 0x24, 0x40, 0x48, 0x89, 0x6C, 0x24,
    0x48, 0x48, 0x89, 0x74, 0x24, 0x50, 0x49, 0x8B, 0xE9, 0x48, 0x8B, 0xF2};

static constexpr size_t dataSetSize = sizeof(dataSet) / sizeof(uint8_t);

TEST(SimilarPattern, Avx2) {
    const CpuInfo& cpuInfo = CpuInfo::GetCpuInfo();
    if (!cpuInfo.avx2Supported) {
        GTEST_SKIP();
    }

    const Scanner<ScanMode::Avx2> scanner(
        "40 57 48 83 EC ? 48 C7 44 24 ? ? ? ? ? 48 89 5C 24 ? 48 89 6C 24 ? 48 "
        "89 74 24 ? 49 8B E9 48 8B F2");

    const uint8_t* pointer =
        scanner.Find((void*)dataSet, dataSetSize).Get<uint8_t>();
    const size_t offset = ((uint64_t)pointer - (uint64_t)dataSet);

    ASSERT_EQ(offset, 0x24);
}

TEST(SimilarPattern, Sse42) {
    const CpuInfo& cpuInfo = CpuInfo::GetCpuInfo();
    if (!cpuInfo.sse42Supported) {
        GTEST_SKIP();
    }

    const Scanner<ScanMode::Sse42> scanner(
        "40 57 48 83 EC ? 48 C7 44 24 ? ? ? ? ? 48 89 5C 24 ? 48 89 6C 24 ? 48 "
        "89 74 24 ? 49 8B E9 48 8B F2");

    const uint8_t* pointer =
        scanner.Find((void*)dataSet, dataSetSize).Get<uint8_t>();
    const size_t offset = ((uint64_t)pointer - (uint64_t)dataSet);

    ASSERT_EQ(offset, 0x24);
}

TEST(SimilarPattern, Scalar) {
    const Scanner<ScanMode::Scalar> scanner(
        "40 57 48 83 EC ? 48 C7 44 24 ? ? ? ? ? 48 89 5C 24 ? 48 89 6C 24 ? 48 "
        "89 74 24 ? 49 8B E9 48 8B F2");

    const uint8_t* pointer =
        scanner.Find((void*)dataSet, dataSetSize).Get<uint8_t>();
    const size_t offset = ((uint64_t)pointer - (uint64_t)dataSet);

    ASSERT_EQ(offset, 0x24);
}
