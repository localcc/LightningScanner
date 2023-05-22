#pragma once

namespace LightningScanner {

/**
 * ScanResult containing the first occurrence of the pattern
 * in the binary, or nullptr.
 *
 * \headerfile ScanResult.hpp <LightningScanner/ScanResult.hpp>
 */
class ScanResult {
public:
    /**
     * Create a new ScanResult instance
     *
     * \param addr memory address
     */
    explicit ScanResult(void* addr) : m_Addr(addr) {}

    /**
     * Get this ScanResult's address and cast it to T*
     *
     * \param offset the offset to add to the current address.
     *
     * \tparam T type to cast to.
     */
    template <typename T>
    T* Get(size_t offset = 0) {
        return (T*)((char*)m_Addr + offset);
    }

private:
    void* m_Addr;
};

} // namespace LightningScanner