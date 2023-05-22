#pragma once
#include <LightningScanner/Pattern.hpp>
#include <LightningScanner/ScanResult.hpp>
#include <vector>

namespace LightningScanner {

/**
 * Scan the binary using scalar scanning.
 *
 * \headerfile Scalar.hpp <LightningScanner/backends/Scalar.hpp>
 *
 * \param{in} data pattern data.
 * \param{in} startAddr address to start the search from
 * \param{in} size binary size of the search area
 */
ScanResult FindScalar(const Pattern& data, void* startAddr, size_t size);

} // namespace LightningScanner