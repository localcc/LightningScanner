#include <LightningScanner/backends/Avx2.hpp>
#include <immintrin.h>

namespace LightningScanner {

ScanResult FindAvx2(const Pattern& patternData, void* startAddr, size_t size) {
    constexpr size_t UNIT_SIZE = 32;

    size_t processedSize = 0;

    __m256i pattern = _mm256_load_si256((__m256i*)patternData.data.data());
    __m256i mask = _mm256_load_si256((__m256i*)patternData.mask.data());
    __m256i allZeros = _mm256_set1_epi8(0x00);

    for (size_t chunk = 0; chunk < size; chunk++) {
        __m256i chunkData =
            _mm256_loadu_si256((__m256i*)((char*)startAddr + chunk));

        __m256i blend = _mm256_blendv_epi8(allZeros, chunkData, mask);
        __m256i eq = _mm256_cmpeq_epi8(pattern, blend);

        if (_mm256_movemask_epi8(eq) == 0xffffffff) {
            processedSize += UNIT_SIZE;

            if (processedSize < patternData.unpaddedSize) {
                chunk += UNIT_SIZE - 1;
                pattern = _mm256_load_si256(
                    (__m256i*)(patternData.data.data() + processedSize));
                mask = _mm256_load_si256(
                    (__m256i*)(patternData.mask.data() + processedSize));
            } else {
                char* matchAddr =
                    (char*)startAddr + chunk - processedSize + UNIT_SIZE;
                return ScanResult((void*)matchAddr);
            }
        } else {
            pattern = _mm256_load_si256((__m256i*)patternData.data.data());
            mask = _mm256_load_si256((__m256i*)patternData.mask.data());
            processedSize = 0;
        }
    }

    return ScanResult(nullptr);
}

} // namespace LightningScanner