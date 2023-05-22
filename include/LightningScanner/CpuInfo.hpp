#pragma once

namespace LightningScanner {

/**
 * Cpu information
 *
 * \headerfile CpuInfo.hpp <LightningScanner/CpuInfo.hpp>
 */
struct CpuInfo {
    /** Is SSE4.2 supported? */
    bool sse42Supported = false;
    /** Is AVX2 supported? */
    bool avx2Supported = false;

    /**
     * Get the cpu information
     */
    static const CpuInfo& GetCpuInfo();

private:
    CpuInfo();
};

} // namespace LightningScanner