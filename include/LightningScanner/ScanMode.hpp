#pragma once

/**
 * Scanner ScanMode
 *
 * \headerfile ScanMode.hpp <LightningScanner/ScanMode.hpp>
 */
enum class ScanMode {
    /** Scalar scan mode */
    Scalar,
    /** Scan mode that uses SSE4.2 SIMD instructions */
    Sse42,
    /** Scan mode that uses AVX2 SIMD instructions */
    Avx2,
};