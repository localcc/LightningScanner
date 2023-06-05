#pragma once
#include <LightningScanner/allocator/AlignedAllocator.hpp>
#include <cmath>
#include <cstdint>
#include <string_view>
#include <vector>

namespace LightningScanner {

/**
 * IDA-style pattern
 *
 * \headerfile Pattern.hpp <LightningScanner/Pattern.hpp>
 */
struct Pattern {
    /**
     * Memory alignment for inner data/mask elements of this pattern.
     */
    static constexpr size_t Alignment = 32;

    /**
     * Create a new Pattern instance from a compile-time string.
     *
     * \tparam Len pattern string length.
     *
     * \param pattern pattern string.
     */
    template <size_t Len>
    constexpr Pattern(const char (&pattern)[Len]) : Pattern(pattern, Len - 1) {}

    /**
     * Create a new Pattern instance from a `string_view`
     *
     * \param pattern pattern string.
     */
    Pattern(const std::string_view pattern)
        : Pattern(pattern.data(), pattern.size()) {}

    /**
     * Create a new Pattern instance from a c-string and its length
     *
     * \param pattern pattern string.
     * \param len pattern string length.
     */
    Pattern(const char* pattern, const size_t len) {
        size_t byteIndex = 0;

        for (size_t i = 0; i < len; i++) {
            char symbol = pattern[i];
            char nextSymbol = ((i + 1) < len) ? pattern[i + 1] : 0;
            if (symbol == ' ')
                continue;

            if (symbol == '?') {
                data.push_back(0x00);
                mask.push_back(0x00);

                if (nextSymbol == '?') {
                    ++i;
                }

                ++byteIndex;
                continue;
            }

            uint8_t byte = CharToByte(symbol) << 4 | CharToByte(nextSymbol);

            data.push_back(byte);
            mask.push_back(0xff);

            ++i;
        }

        unpaddedSize = data.size();

        size_t count = (size_t)std::ceil((float)data.size() / Alignment);
        size_t paddingSize = count * Alignment - data.size();

        for (size_t i = 0; i < paddingSize; i++) {
            data.push_back(0x00);
            mask.push_back(0x00);
        }
    }

public:
    /** Pattern binary data */
    std::vector<uint8_t, AlignedAllocator<uint8_t, Alignment>> data{};
    /** Pattern binary data mask */
    std::vector<uint8_t, AlignedAllocator<uint8_t, Alignment>> mask{};
    /** Unpadded pattern size */
    size_t unpaddedSize{};

private:
    static uint8_t CharToByte(char symbol) {
        if (symbol >= 'a' && symbol <= 'z')
            return symbol - 'a' + 0xA;
        else if (symbol >= 'A' && symbol <= 'Z')
            return symbol - 'A' + 0xA;
        else if (symbol >= '0' && symbol <= '9')
            return symbol - '0';
        else
            return 0;
    }
};

} // namespace LightningScanner