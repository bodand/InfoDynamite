//
// Created by tudom on 2019-12-22.
//

#include <cstring>
#include <fstream>
#include <variant>
#include <algorithm>
#include <memory>

#include <elf.h>

#include "../include.hpp"
#include "endian.hpp"

#include LIBNM_INCLUDE_HEADER_N(nm.hpp)
#include LIBNM_INCLUDE_HEADER_N(exec.h)
//&!off
#include LIBNM_INCLUDE_HEADER_N(exception/CorruptedELFObject.hpp)
//&!on

[[nodiscard]] LIBNM_API
bool libnm::IsSharedObject(std::string_view file) noexcept {
    char magic[4];
    std::ifstream str(file.data(), std::ios::in | std::ios::binary);
    str.read(magic, 4 * sizeof(magic[0]));
    return !std::strncmp(magic, "\177ELF", 4);
}

[[nodiscard]] LIBNM_LOCAL
std::vector<std::string> libnm::detail::ListExports(std::string_view filen) {
    std::ifstream file{filen.data(), std::ios::in | std::ios::binary};
    std::array<typename decltype(file)::char_type, sizeof(Elf64_Ehdr)> header{};

    file.read(header.data(), header.size() * sizeof(decltype(header)::value_type));

    if (header[4] == 1) { // 32-bit ELF object
        Elf32_Ehdr ehdr;
        std::memcpy(&ehdr, header.data(), sizeof(ehdr));
        return HandleElfEhdr(ehdr, file);
    } else if (header[4] == 2) { // 64-bit ELF object
        Elf64_Ehdr ehdr;
        std::memcpy(&ehdr, header.data(), sizeof(ehdr));
        return HandleElfEhdr(ehdr, file);
    } else {
        throw unexplainable_elf_bit_format{(uint8_t) header[4]};
    }
}

template<class ElfEhdr, class ElfShdr, class StreamT>
[[nodiscard]] LIBNM_LOCAL
std::vector<ElfShdr> libnm::detail::GetSectionHeaders(const ElfEhdr& ehdr,
                                                      std::basic_istream<StreamT>& file) {
    BOOST_STATIC_ASSERT_MSG(std::is_same_v<ElfEhdr, Elf32_Ehdr> || std::is_same_v<ElfEhdr, Elf64_Ehdr>,
                            "ElfEhdr is not of appropriate type");
    BOOST_STATIC_ASSERT_MSG(std::is_same_v<ElfShdr, Elf32_Shdr> || std::is_same_v<ElfShdr, Elf64_Shdr>,
                            "ElfShdr is not of appropriate type");
    BOOST_STATIC_ASSERT_MSG(
           (std::is_same_v<ElfEhdr, Elf32_Ehdr>
            && std::is_same_v<ElfShdr, Elf32_Shdr>)
           || (std::is_same_v<ElfEhdr, Elf64_Ehdr>
               && std::is_same_v<ElfShdr, Elf64_Shdr>),
           "ElfEhdr and ElfShdr are not matching in their 32/64-bitness");

    using streamChar = typename std::remove_reference_t<decltype(file)>::char_type;

    if (ehdr.e_shnum == 0)
        throw no_sections{};

    if (ehdr.e_shnum < ehdr.e_shstrndx)
        throw inconsistent_section_header_table{};

    if (ehdr.e_shentsize < sizeof(ElfShdr))
        throw inconsistent_section_header_size{};

    std::vector<ElfShdr> ret(ehdr.e_shnum);

    file.seekg(static_cast<long>(ehdr.e_shoff), std::ios::beg);

    for (std::size_t i = 0; i < ret.size(); ++i) {
        std::array<
               streamChar,
               sizeof(ElfShdr) / sizeof(streamChar)
        > rawShdr{};
        long rawSize = rawShdr.size() * sizeof(streamChar);

        file.read(rawShdr.data(), rawSize);
        if (file.gcount() < rawSize)
            throw corrupted_elf_object{};

        std::memcpy(&ret[i], rawShdr.data(), sizeof(ElfShdr));

        FixEndian(ehdr, ret[i]);
    }

    return ret;
}

template<class ElfEhdr, class StreamT>
[[nodiscard]] LIBNM_LOCAL
std::vector<std::string> libnm::detail::HandleElfEhdr(ElfEhdr ehdr,
                                                      std::basic_istream<StreamT>& file) {
    BOOST_STATIC_ASSERT_MSG(std::is_same_v<ElfEhdr, Elf32_Ehdr> || std::is_same_v<ElfEhdr, Elf64_Ehdr>,
                            "ElfEhdr is not of appropriate type");

    FixEndian(ehdr); // fix possible endianness mismatch

    std::vector<etosh_t<ElfEhdr>> sectionHeaders;
    try {
        sectionHeaders = GetSectionHeaders(ehdr, file); // get all section headers from the object
    } catch (no_sections&) {
        return {};
    } catch (...) {
        throw;
    }

    auto stringIndexTable = GetStringIndexTable(ehdr, sectionHeaders, file); // slurp the string index table into memory

    std::size_t dynstrSize;
    auto dynstr = ReadDynStr(GetDynStr(stringIndexTable, sectionHeaders),
                             file,
                             dynstrSize); // slurp .dynstr into memory

    auto dynsym = GetDynSym(stringIndexTable, sectionHeaders); // select the .dynsym section

    std::vector<std::string> ret;
    etosym_t<ElfEhdr> sym;

    file.seekg(static_cast<long>(dynsym.sh_offset), std::ios::beg);

    for (auto dynsymSize = dynsym.sh_size; dynsymSize > 0; dynsymSize -= sizeof(sym)) {
        std::array<StreamT, sizeof(sym) / sizeof(StreamT)> buf;
        long rawSize = buf.size() * sizeof(StreamT);

        file.read(buf.data(), rawSize);
        if (file.gcount() < rawSize)
            throw corrupted_elf_object{};

        std::memcpy(&sym, buf.data(), sizeof(sym));
        FixEndian(ehdr, sym);

        if (!sym.st_name || sym.st_name >= dynstrSize)
            continue;

        if (!IsFunction(sym))
            continue;

        std::string name{ConcoctNameFromElfSym(dynstr.get(), sym)};

        if (IsSystemFunction(name))
            continue;

        ret.push_back(name);
    }

    return ret;
}

template<class ElfEhdr, class ElfShdr, class StreamT>
[[nodiscard]] LIBNM_LOCAL
std::string libnm::detail::GetStringIndexTable(const ElfEhdr& ehdr,
                                               const std::vector<ElfShdr>& sections,
                                               std::basic_istream<StreamT>& file) noexcept {
    BOOST_STATIC_ASSERT_MSG(std::is_same_v<ElfEhdr, Elf32_Ehdr> || std::is_same_v<ElfEhdr, Elf64_Ehdr>,
                            "ElfEhdr is not of appropriate type");
    BOOST_STATIC_ASSERT_MSG(std::is_same_v<ElfShdr, Elf32_Shdr> || std::is_same_v<ElfShdr, Elf64_Shdr>,
                            "ElfShdr is not of appropriate type");
    BOOST_STATIC_ASSERT_MSG(
           (std::is_same_v<ElfEhdr, Elf32_Ehdr>
            && std::is_same_v<ElfShdr, Elf32_Shdr>)
           || (std::is_same_v<ElfEhdr, Elf64_Ehdr>
               && std::is_same_v<ElfShdr, Elf64_Shdr>),
           "ElfEhdr and ElfShdr are not matching in their 32/64-bitness");

    auto& stringSection = sections[ehdr.e_shstrndx];
    file.seekg(static_cast<long>(stringSection.sh_offset), std::ios::beg);

    auto size = stringSection.sh_size;
    std::unique_ptr<StreamT[]> ptr{new StreamT[stringSection.sh_size]};

    file.read(ptr.get(), static_cast<std::streamsize>(size * sizeof(StreamT)));

    return std::string{ptr.get(), size};
}

template<class ElfShdr>
[[nodiscard]] LIBNM_LOCAL
const ElfShdr& libnm::detail::FindSection(std::string_view sectionName,
                                          std::string_view stringIndexTable,
                                          const std::vector<ElfShdr>& sections) noexcept {
    BOOST_STATIC_ASSERT_MSG(std::is_same_v<ElfShdr, Elf32_Shdr> || std::is_same_v<ElfShdr, Elf64_Shdr>,
                            "ElfShdr is not of appropriate type");

    return *std::find_if(sections.begin(), sections.end(), [stringIndexTable, sectionName](const ElfShdr& shdr) {
      return !strcmp(stringIndexTable.data() + shdr.sh_name, sectionName.data());
    });
}


template<class ElfShdr>
[[nodiscard]] LIBNM_LOCAL
const ElfShdr& libnm::detail::GetDynStr(std::string_view stringIndexTable,
                                        const std::vector<ElfShdr>& sections) noexcept {
    BOOST_STATIC_ASSERT_MSG(std::is_same_v<ElfShdr, Elf32_Shdr> || std::is_same_v<ElfShdr, Elf64_Shdr>,
                            "ElfShdr is not of appropriate type");

    return FindSection(".dynstr", stringIndexTable, sections);
}


template<class ElfShdr>
[[nodiscard]] LIBNM_LOCAL
const ElfShdr& libnm::detail::GetDynSym(std::string_view stringIndexTable,
                                        const std::vector<ElfShdr>& sections) noexcept {
    BOOST_STATIC_ASSERT_MSG(std::is_same_v<ElfShdr, Elf32_Shdr> || std::is_same_v<ElfShdr, Elf64_Shdr>,
                            "ElfShdr is not of appropriate type");

    return FindSection(".dynsym", stringIndexTable, sections);
}


template<class ElfShdr, class StreamT>
[[nodiscard]] LIBNM_LOCAL
std::unique_ptr<StreamT[]> libnm::detail::ReadDynStr(const ElfShdr& dynstr,
                                                     std::basic_istream<StreamT>& file,
                                                     std::size_t& dynstrSize) noexcept {
    BOOST_STATIC_ASSERT_MSG(std::is_same_v<ElfShdr, Elf32_Shdr> || std::is_same_v<ElfShdr, Elf64_Shdr>,
                            "ElfShdr is not of appropriate type");

    dynstrSize = dynstr.sh_size;

    std::unique_ptr<StreamT[]> ret{new StreamT[dynstrSize]};

    file.seekg(static_cast<long>(dynstr.sh_offset), std::ios::beg);
    file.read(ret.get(), static_cast<std::streamsize>(dynstrSize * sizeof(StreamT)));

    return ret;
}

template<class ElfSym>
[[nodiscard]] LIBNM_LOCAL
std::string libnm::detail::ConcoctNameFromElfSym(std::string_view dynstr,
                                                 const ElfSym& sym) {
    BOOST_STATIC_ASSERT_MSG(std::is_same_v<ElfSym, Elf32_Sym> || std::is_same_v<ElfSym, Elf64_Sym>,
                            "ElfSym is not of appropriate type");

    return {dynstr.data() + sym.st_name};
}

template<class ElfSym>
bool libnm::detail::IsFunction(const ElfSym& sym) noexcept {
    BOOST_STATIC_ASSERT_MSG(std::is_same_v<ElfSym, Elf32_Sym> || std::is_same_v<ElfSym, Elf64_Sym>,
                            "ElfSym is not of appropriate type");

    constexpr auto stType = [](const ElfSym& sym) {
      if constexpr (is_32_elf_v<ElfSym>) {
          return ELF32_ST_TYPE(sym.st_info);
      } else if constexpr (is_64_elf_v<ElfSym>) {
          return ELF64_ST_TYPE(sym.st_info);
      } else {
          return 0;
      }
    };

    return stType(sym) == STT_FUNC;
}

bool libnm::detail::IsSystemFunction(std::string_view name) noexcept {
    return name.substr(0, 6) == "__cxa_"
           || name == "_init"
           || name == "_fini";
}
