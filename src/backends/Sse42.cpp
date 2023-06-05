#include <LightningScanner/backends/Sse42.hpp>
#include <smmintrin.h>

namespace LightningScanner {

ScanResult FindSse42(const Pattern& patternData, void* startAddr, size_t size) {
    constexpr size_t UNIT_SIZE = 16;

    size_t processedSize = 0;

    __m128i pattern = _mm_load_si128((__m128i*)patternData.data.data());
    __m128i mask = _mm_load_si128((__m128i*)patternData.mask.data());
    __m128i allZeros = _mm_set1_epi8(0x00);

    for (size_t chunk = 0; chunk < size; chunk++) {
        __m128i chunkData =
            _mm_loadu_si128((__m128i*)((char*)startAddr + chunk));

        __m128i blend = _mm_blendv_epi8(allZeros, chunkData, mask);
        __m128i eq = _mm_cmpeq_epi8(pattern, blend);

        if (_mm_movemask_epi8(eq) == 0xffff) {
            processedSize += UNIT_SIZE;

            if (processedSize < patternData.unpaddedSize) {
                chunk += UNIT_SIZE - 1;
                pattern = _mm_load_si128(
                    (__m128i*)(patternData.data.data() + processedSize));
                mask = _mm_load_si128(
                    (__m128i*)(patternData.mask.data() + processedSize));
            } else {
                char* matchAddr =
                    (char*)startAddr + chunk - processedSize + UNIT_SIZE;
                return ScanResult((void*)matchAddr);
            }
        } else {
            pattern = _mm_load_si128((__m128i*)patternData.data.data());
            mask = _mm_load_si128((__m128i*)patternData.mask.data());
            processedSize = 0;
        }
    }

    return ScanResult(nullptr);
}

} // namespace LightningScanner