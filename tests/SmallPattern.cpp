#include <LightningScanner/CpuInfo.hpp>
#include <LightningScanner/LightningScanner.hpp>

#include "Shared.hpp"
#include <gtest/gtest.h>

/**
 * Check that a pattern that is smaller than the Avx2/Sse42 register size scans
 * correctly.
 */

using namespace LightningScanner;

TEST(SmallPattern, Avx2) {
    const CpuInfo& cpuInfo = CpuInfo::GetCpuInfo();
    if (!cpuInfo.avx2Supported) {
        GTEST_SKIP();
    }

    const Scanner<ScanMode::Avx2> scanner("a0 9e 87 00 ?? 5c");
    const uint8_t* pointer =
        scanner.Find((void*)dataSet, dataSetSize).Get<uint8_t>();
    const size_t offset = ((uint64_t)pointer - (uint64_t)dataSet);

    ASSERT_EQ(offset, 0x24);
}

TEST(SmallPattern, Sse42) {
    const CpuInfo& cpuInfo = CpuInfo::GetCpuInfo();
    if (!cpuInfo.sse42Supported) {
        GTEST_SKIP();
    }

    const Scanner<ScanMode::Sse42> scanner("a0 9e 87 00 ?? 5c");
    const uint8_t* pointer =
        scanner.Find((void*)dataSet, dataSetSize).Get<uint8_t>();
    const size_t offset = ((uint64_t)pointer - (uint64_t)dataSet);

    ASSERT_EQ(offset, 0x24);
}

TEST(SmallPattern, Scalar) {
    const Scanner<ScanMode::Scalar> scanner("a0 9e 87 00 ?? 5c");
    const uint8_t* pointer =
        scanner.Find((void*)dataSet, dataSetSize).Get<uint8_t>();
    const size_t offset = ((uint64_t)pointer - (uint64_t)dataSet);

    ASSERT_EQ(offset, 0x24);
}