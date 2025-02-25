#include <LightningScanner/backends/StdFind.hpp>
#include <algorithm>

namespace LightningScanner {

ScanResult FindStdFind(const Pattern& data, void* startAddr, size_t size) {
    uint8_t* start = static_cast<uint8_t*>(startAddr);
    uint8_t* end =
        static_cast<uint8_t*>(startAddr) + size - data.unpaddedSize + 1;

    uint8_t element = data.data[0];
    while ((start = std::find(start, end, element)) != end) {
        bool found = true;

        for (size_t i = 0; i < data.unpaddedSize; i++) {
            uint8_t searchElement = data.data[i] & data.mask[i];
            uint8_t foundElement = start[i] & data.mask[i];
            if (searchElement != foundElement) {
                found = false;
                break;
            }
        }

        if (found) {
            return ScanResult(start);
        }

        start++;
    }

    return ScanResult(nullptr);
}

} // namespace LightningScanner