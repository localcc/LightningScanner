#include <LightningScanner/backends/Sse42.hpp>

namespace LightningScanner {

ScanResult FindScalar(const Pattern& patternData, void* startAddr,
                      size_t size) {
    uint8_t* binary = (uint8_t*)startAddr;

    for (size_t binaryOffset = 0; binaryOffset < size; ++binaryOffset) {
        bool found = true;
        for (size_t patternOffset = 0; patternOffset < patternData.data.size();
             patternOffset++) {
            if (patternData.mask[patternOffset] == 0x00)
                continue;
            if (*(binary + binaryOffset + patternOffset) !=
                patternData.data[patternOffset]) {
                found = false;
                break;
            }
        }

        if (found) {
            return ScanResult((void*)(binary + binaryOffset));
        }
    }

    return ScanResult(nullptr);
}

} // namespace LightningScanner