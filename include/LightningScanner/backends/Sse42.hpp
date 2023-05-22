#pragma once
#include <LightningScanner/Pattern.hpp>
#include <LightningScanner/ScanResult.hpp>
#include <vector>

namespace LightningScanner {

/**
 * Scan the binary using SSE4.2 SIMD instructions.
 *
 * \headerfile Sse42.hpp <LightningScanner/backends/Sse42.hpp>
 *
 * \param{in} data pattern data.
 * \param{in} startAddr address to start the search from
 * \param{in} size binary size of the search area
 */
ScanResult FindSse42(const Pattern& data, void* startAddr, size_t size);

} // namespace LightningScanner