#include <LightningScanner/CpuInfo.hpp>
#include <cstdint>

namespace LightningScanner {

#if defined(_MSC_VER) && !defined(__clang__)
#include <intrin.h>
#define cpuid(info, x) __cpuidex(info, x, 0)
#else
#if !defined(__aarch64__)
#include <cpuid.h>
void cpuid(int info[4], int infoType) {
    __cpuid_count(infoType, 0, info[0], info[1], info[2], info[3]);
}
#endif
#endif

CpuInfo::CpuInfo() {
#if !defined(__aarch64__)
    int32_t info[4];
    cpuid(info, 0);
    int32_t idsAmount = info[0];

    if (idsAmount >= 1) {
        const int32_t SSE42_MASK = (1 << 20);

        int32_t cpuInfo[4];
        cpuid(cpuInfo, 1);

        sse42Supported = cpuInfo[2] & SSE42_MASK;
    }

    if (idsAmount >= 7) {
        const int32_t AVX2_MASK = (1 << 5);

        int32_t cpuInfo[4];
        cpuid(cpuInfo, 7);

        avx2Supported = cpuInfo[1] & AVX2_MASK;
    }
#endif
}

const CpuInfo& CpuInfo::GetCpuInfo() {
    static const CpuInfo info;
    return info;
}

} // namespace LightningScanner