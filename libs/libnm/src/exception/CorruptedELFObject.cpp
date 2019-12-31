//
// Created by tudom on 2019-12-30.
//

#include <string>
#include <charconv>
#include <array>

#include <sprout/math/pow.hpp>
#include <sprout/math/iround.hpp>

#include "../include.hpp"
//&!off
#include LIBNM_INCLUDE_HEADER_N(exception/CorruptedELFObject.hpp)
//&!on

const char* libnm::corrupted_elf_object::what() const noexcept {
    return "The ELF object is found to have become corrupted. Further information unavailable.";
}

template<class T>
LIBNM_LOCAL
constexpr auto cs(T i) -> T {
    if (i >= 10) {
        return 1 + cs(i % 10);
    }
    return 1;
}

const char* libnm::unexplainable_elf_bit_format::what() const noexcept {
    static std::string str;
    str = "Byte signifying 32/64-bitness expected to be `1` or `2` but was `" + _byte + "`.";
    return str.c_str();
}

libnm::unexplainable_elf_bit_format::unexplainable_elf_bit_format(uint8_t byte) {
    namespace sm = sprout::math;

    std::array<char, cs(sm::iround<std::size_t>(sm::pow(2, sizeof(byte))))> tmpString{};
    if (auto[end, ec] = std::to_chars(tmpString.data(), tmpString.data() + tmpString.size(), byte);
           ec == std::errc()) {
        _byte = {tmpString.data(), static_cast<std::size_t>(end - tmpString.data())};
    } else {
        _byte = "<?>";
    }
}

const char* libnm::no_sections::what() const noexcept {
    return "Elf object contains no sections.";
}

const char* libnm::inconsistent_section_header_table::what() const noexcept {
    return "String Index Table's position is greater than the amount of section headers.";
}

const char* libnm::inconsistent_section_header_size::what() const noexcept {
    return "Section-header's size is declared different from which the system expects.";
}
