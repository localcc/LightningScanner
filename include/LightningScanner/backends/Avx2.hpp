#pragma once
#include <LightningScanner/Pattern.hpp>
#include <LightningScanner/ScanResult.hpp>
#include <vector>

namespace LightningScanner {

/**
 * Scan the binary using AVX2 SIMD instructions.
 *
 * \headerfile Avx2.hpp <LightningScanner/backends/Avx2.hpp>
 *
 * \param{in} data pattern data.
 * \param{in} startAddr address to start the search from
 * \param{in} size binary size of the search area
 */
ScanResult FindAvx2(const Pattern& data, void* startAddr, size_t size);

} // namespace LightningScanner