#include <LightningScanner/CpuInfo.hpp>
#include <cstdint>
#include <intrin.h>

namespace LightningScanner {

CpuInfo::CpuInfo() {
    int32_t info[4];
    __cpuid(info, 0);
    int32_t idsAmount = info[0];

    if (idsAmount >= 1) {
        const int32_t SSE42_MASK = (1 << 20);

        int32_t cpuInfo[4];
        __cpuidex(cpuInfo, 1, 0);

        sse42Supported = cpuInfo[2] & SSE42_MASK;
    }

    if (idsAmount >= 7) {
        const int32_t AVX2_MASK = (1 << 5);

        int32_t cpuInfo[4];
        __cpuidex(cpuInfo, 7, 0);

        avx2Supported = cpuInfo[1] & AVX2_MASK;
    }
}

const CpuInfo& CpuInfo::GetCpuInfo() {
    static const CpuInfo info;
    return info;
}

} // namespace LightningScanner