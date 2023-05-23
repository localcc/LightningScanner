#pragma once
#include <cstddef>
#include <limits>
#include <new>

namespace LightningScanner {

// clang-format off
/**
 * AlignedAllocator used to allocate memory on the specified alignment.
 *
 * \headerfile AlignedAllocator.hpp <LightningScanner/allocator/AlignedAllocator.hpp>
 *
 * \tparam T element type to allocate.
 * \tparam Alignment alignment to allocate on.
 */
// clang-format on
template <typename T, size_t Alignment>
class AlignedAllocator {
public:
    /** Allocated value type */
    typedef T value_type;

    AlignedAllocator() = default;

    template <typename U>
    constexpr AlignedAllocator(const AlignedAllocator<U, Alignment>&) noexcept {
    }

    /**
     * Struct for rebinding other instances of this allocator
     */
    template <typename U>
    struct rebind {
        typedef AlignedAllocator<U, Alignment> other;
    };

    /**
     * Allocate elements from memory
     *
     * \param n amount of T's to allocate.
     */
    T* allocate(size_t n) {
        if (n > std::numeric_limits<size_t>::max() / sizeof(T))
            throw std::bad_array_new_length();

        auto const bytesToAllocate = n * sizeof(T);
        // clang-format off
        return (T*)(::operator new[](bytesToAllocate, std::align_val_t(Alignment)));
        // clang-format on
    }

    /**
     * Deallocate elements from memory
     *
     * \param{in} data data pointer to deallocate.
     * \param{in} n amount of elements to deallocate from the data pointer.
     */
    void deallocate(T* data, size_t n) noexcept {
        ::operator delete[](data, std::align_val_t(Alignment));
    }

    bool operator==(const AlignedAllocator&) { return true; }
    bool operator!=(const AlignedAllocator&) { return false; }
};

} // namespace LightningScanner