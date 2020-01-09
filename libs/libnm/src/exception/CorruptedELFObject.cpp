//
// Created by tudom on 2019-12-30.
//

#include <string>
#include <charconv>
#include <array>

#include "../include.hpp"
//&!off
#include LIBNM_INCLUDE_HEADER_N(exception/CorruptedELFObject.hpp)
//&!on

LIBNM_API
const char* libnm::corrupted_elf_object::what() const noexcept {
    return "The ELF object is found to have become corrupted. Further information unavailable.";
}

template<class T>
LIBNM_LOCAL
constexpr auto g10d(T i) {
    auto d = 10;
    while (i % d != i) {
        d *= 10;
    }
    return d / 10;
}

template<class T>
LIBNM_LOCAL
constexpr auto sl(T i) -> T {
    if (i >= 10) {
        return 1 +
               sl(i % g10d(i));
    }
    return 1;
}

template<class T>
LIBNM_LOCAL
inline constexpr T pow(T const& x, std::size_t n) {
    return n > 0 ? x * pow(x, n - 1)
                 : 1;
}

LIBNM_API
const char* libnm::unexplainable_elf_bit_format::what() const noexcept {
    static std::string str;
    str = "Byte signifying 32/64-bitness expected to be `1` or `2` but was `" + _byte + "`.";
    return str.c_str();
}

LIBNM_API
libnm::unexplainable_elf_bit_format::unexplainable_elf_bit_format(uint8_t byte) {
    std::array<char, sl(pow(2, sizeof(byte)))> tmpString{};
    if (auto[end, ec] = std::to_chars(tmpString.data(), tmpString.data() + tmpString.size(), byte);
           ec == std::errc()) {
        _byte = {tmpString.data(), static_cast<std::size_t>(end - tmpString.data())};
    } else {
        _byte = "<?>";
    }
}

LIBNM_API
const char* libnm::no_sections::what() const noexcept {
    return "Elf object contains no sections.";
}

LIBNM_API
const char* libnm::inconsistent_section_header_table::what() const noexcept {
    return "String Index Table's position is greater than the amount of section headers.";
}

LIBNM_API
const char* libnm::inconsistent_section_header_size::what() const noexcept {
    return "Section-header's size is declared different from which the system expects.";
}
