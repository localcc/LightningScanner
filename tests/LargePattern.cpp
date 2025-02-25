#include <LightningScanner/CpuInfo.hpp>
#include <LightningScanner/LightningScanner.hpp>

#include "Shared.hpp"
#include <gtest/gtest.h>

/**
 * Check that a pattern that is larger than the Avx2/Sse42 register size scans
 * correctly.
 */

using namespace LightningScanner;

TEST(LargePattern, Avx2) {
    const CpuInfo& cpuInfo = CpuInfo::GetCpuInfo();
    if (!cpuInfo.avx2Supported) {
        GTEST_SKIP();
    }

    const Scanner<ScanMode::Avx2> scanner(
        "42 cd e7 f8 21 5b d6 b8 d1 be 12 0e 85 34 c4 ?? 03 7e bc 7b b9 29 b6 "
        "07 31 7e ?? dd 3e 0a e7 71 f3 b7 76 3f 36 e1 f3 3b c6 e5 ?? f8 97 67 "
        "86 60 ");

    const uint8_t* pointer =
        scanner.Find((void*)dataSet, dataSetSize).Get<uint8_t>();
    const size_t offset = ((uint64_t)pointer - (uint64_t)dataSet);

    ASSERT_EQ(offset, 0x40);
}

TEST(LargePattern, Sse42) {
    const CpuInfo& cpuInfo = CpuInfo::GetCpuInfo();
    if (!cpuInfo.sse42Supported) {
        GTEST_SKIP();
    }

    const Scanner<ScanMode::Sse42> scanner(
        "42 cd e7 f8 21 5b d6 b8 d1 be 12 0e 85 34 c4 ?? 03 7e bc 7b b9 29 b6 "
        "07 31 7e ?? dd 3e 0a e7 71 f3 b7 76 3f 36 e1 f3 3b c6 e5 ?? f8 97 67 "
        "86 60 ");

    const uint8_t* pointer =
        scanner.Find((void*)dataSet, dataSetSize).Get<uint8_t>();
    const size_t offset = ((uint64_t)pointer - (uint64_t)dataSet);

    ASSERT_EQ(offset, 0x40);
}

TEST(LargePattern, StdFind) {
    const Scanner<ScanMode::StdFind> scanner(
        "42 cd e7 f8 21 5b d6 b8 d1 be 12 0e 85 34 c4 ?? 03 7e bc 7b b9 29 b6 "
        "07 31 7e ?? dd 3e 0a e7 71 f3 b7 76 3f 36 e1 f3 3b c6 e5 ?? f8 97 67 "
        "86 60 ");

    const uint8_t* pointer =
        scanner.Find((void*)dataSet, dataSetSize).Get<uint8_t>();
    const size_t offset = ((uint64_t)pointer - (uint64_t)dataSet);

    ASSERT_EQ(offset, 0x40);
}

TEST(LargePattern, Scalar) {
    const Scanner<ScanMode::Scalar> scanner(
        "42 cd e7 f8 21 5b d6 b8 d1 be 12 0e 85 34 c4 ?? 03 7e bc 7b b9 29 b6 "
        "07 31 7e ?? dd 3e 0a e7 71 f3 b7 76 3f 36 e1 f3 3b c6 e5 ?? f8 97 67 "
        "86 60 ");

    const uint8_t* pointer =
        scanner.Find((void*)dataSet, dataSetSize).Get<uint8_t>();
    const size_t offset = ((uint64_t)pointer - (uint64_t)dataSet);

    ASSERT_EQ(offset, 0x40);
}