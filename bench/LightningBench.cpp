#include <LightningScanner/CpuInfo.hpp>
#include <LightningScanner/LightningScanner.hpp>

#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>

std::ostream& operator<<(std::ostream& os, const ScanMode& mode) {
    switch (mode) {
    case ScanMode::Avx2:
        os << "AVX2";
        break;
    case ScanMode::Sse42:
        os << "SSE4.2";
        break;
    case ScanMode::Scalar:
        os << "Scalar";
        break;
    };
    return os;
}

template <ScanMode Mode>
void Bench(uint8_t* data, size_t dataSize, std::string_view pattern) {
    LightningScanner::Scanner<Mode> scanner(pattern);

    auto start = std::chrono::high_resolution_clock::now();
    LightningScanner::ScanResult result = scanner.Find((void*)data, dataSize);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> diff = end - start;
    std::cout
        << "Time to find a 32 byte pattern at the end of a 1GB file using "
        << Mode << ": " << diff.count()
        << " seconds, offset from start: " << std::hex
        << ((uint64_t)result.Get<void>() - (uint64_t)data) << std::dec
        << std::endl;
}

int main() {
    const LightningScanner::CpuInfo& info =
        LightningScanner::CpuInfo::GetCpuInfo();
    std::cout << "Cpu features: " << std::endl;
    std::cout << "SSE4.2: " << info.sse42Supported << std::endl;
    std::cout << "AVX2: " << info.avx2Supported << std::endl;

    std::cout << "Generating a 1GB binary..." << std::endl;
    std::vector<uint8_t> largeBinary;
    largeBinary.resize(1073741824 /* 1gb */);

    uint8_t data[] = {0x48, 0x89, 0x5C, 0x24, 0x00, 0x48, 0x89, 0x6C,
                      0x24, 0x00, 0x48, 0x89, 0x74, 0x24, 0x00, 0x48,
                      0x89, 0x7C, 0x24, 0x00, 0x41, 0x56, 0x41, 0x57,
                      0x4c, 0x8b, 0x79, 0x38, 0xaa, 0xbf, 0xcd, 0x00};
    memcpy(largeBinary.data() + largeBinary.size() - 32, data, 32);

    std::cout << "1GB binary generated, starting scan..." << std::endl;

    Bench<ScanMode::Avx2>(
        largeBinary.data(), largeBinary.size(),
        "48 89 5c 24 ?? 48 89 6c 24 ?? 48 89 74 24 ?? 48 89 7c 24 ?? 41 56 41 "
        "57 4c 8b 79 38 aa bf cd");
    Bench<ScanMode::Sse42>(
        largeBinary.data(), largeBinary.size(),
        "48 89 5c 24 ?? 48 89 6c 24 ?? 48 89 74 24 ?? 48 89 7c 24 ?? 41 56 41 "
        "57 4c 8b 79 38 aa bf cd");
    Bench<ScanMode::Scalar>(
        largeBinary.data(), largeBinary.size(),
        "48 89 5c 24 ?? 48 89 6c 24 ?? 48 89 74 24 ?? 48 89 7c 24 ?? 41 56 41 "
        "57 4c 8b 79 38 aa bf cd");
}