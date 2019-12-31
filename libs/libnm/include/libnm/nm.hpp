//
// Created by tudom on 2019-12-21.
//

#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <array>

#include "_api.hpp"

#ifndef _WIN32
#  include <elf.h>
#endif

/**
 * Contains code for libnm,
 * a library to list exported functions
 * in a dynamic library.
 *
 * Works with Windows and ELF systems.
 *
 * \version 1.0.0
 */
namespace libnm {
  /**
   * Returns a vector of exported functions in a dynamic library.
   * Requires the library to be in the platform specific search
   * path for shared objects/dynamic libraries.
   *
   * On ELF systems this excludes the init and fini routines.
   *
   * \param filename The name of the library to list. This is the whole filename,
   *                  nothing is appended or prepended to it.
   *
   * \return The exported functions from a library
   */
  [[nodiscard]] LIBNM_API
  std::vector<std::string> GetExports(std::string_view);

  /**
   * Returns whether a file is a shared object.
   *
   * Behavior is different for Windows and non-Windows systems:
   * 1) __Windows__
   * As Windows does not use magic numbers to try to guess types of files
   * it just relies on extensions.
   * Therefore, Windows behavior is just to check the file's extension to be
   * `.dll`.
   * 2) __ELF__
   * Elf contains a magic number to be able to check it's type. If the first
   * 4 bytes are "\177ELF" the file is a ELF object.
   *
   * \return The platform specifically checked file's object-ness
   */
  [[nodiscard]] LIBNM_API
  bool IsSharedObject(std::string_view) noexcept;

  namespace detail {
    LIBNM_LOCAL
    std::vector<std::string> ListExports(std::string_view);

#ifndef _WIN32
    template<class T>
    struct LIBNM_LOCAL etos {
    };
    template<>
    struct LIBNM_LOCAL etos<Elf32_Ehdr> {
        using shdr = Elf32_Shdr;
        using sym = Elf32_Sym;
    };
    template<>
    struct LIBNM_LOCAL etos<Elf64_Ehdr> {
        using shdr = Elf64_Shdr;
        using sym = Elf64_Sym;
    };

    template<class ElfEhdr>
    using etosh_t = typename etos<ElfEhdr>::shdr;

    template<class ElfEhdr>
    using etosym_t = typename etos<ElfEhdr>::sym;

    template<class ElfType>
    constexpr const bool is_64_elf_v = std::is_same_v<ElfType, Elf64_Ehdr>
                                       || std::is_same_v<ElfType, Elf64_Shdr>
                                       || std::is_same_v<ElfType, Elf64_Sym>;

    template<class ElfType>
    constexpr const bool is_32_elf_v = std::is_same_v<ElfType, Elf32_Ehdr>
                                       || std::is_same_v<ElfType, Elf32_Shdr>
                                       || std::is_same_v<ElfType, Elf32_Sym>;


    template<class ElfEhdr, class ElfShdr = etosh_t<ElfEhdr>, class StreamT>
    [[nodiscard]] LIBNM_LOCAL
    std::vector<ElfShdr> GetSectionHeaders(const ElfEhdr&,
                                           std::basic_istream<StreamT>&);

    template<class ElfEhdr, class ElfShdr, class StreamT>
    [[nodiscard]] LIBNM_LOCAL
    std::string GetStringIndexTable(const ElfEhdr&,
                                    const std::vector<ElfShdr>&,
                                    std::basic_istream<StreamT>&) noexcept;

    template<class ElfShdr>
    [[nodiscard]] LIBNM_LOCAL
    const ElfShdr& FindSection(std::string_view,
                               std::string_view,
                               const std::vector<ElfShdr>&) noexcept;

    template<class ElfShdr>
    [[nodiscard]] LIBNM_LOCAL
    const ElfShdr& GetDynStr(std::string_view,
                             const std::vector<ElfShdr>&) noexcept;

    template<class ElfShdr>
    [[nodiscard]] LIBNM_LOCAL
    const ElfShdr& GetDynSym(std::string_view,
                             const std::vector<ElfShdr>&) noexcept;

    template<class ElfShdr, class StreamT>
    [[nodiscard]] LIBNM_LOCAL
    std::unique_ptr<StreamT[]> ReadDynStr(const ElfShdr&,
                                          std::basic_istream<StreamT>&,
                                          std::size_t&) noexcept;

    template<class ElfSym>
    [[nodiscard]] LIBNM_LOCAL
    std::string ConcoctNameFromElfSym(std::string_view,
                                      const ElfSym&);

    template<class ElfSym>
    [[nodiscard]] LIBNM_LOCAL
    bool IsFunction(const ElfSym&) noexcept;

    [[nodiscard]] LIBNM_LOCAL
    bool IsSystemFunction(std::string_view) noexcept;

    template<class ElfEhdr, class StreamT>
    [[nodiscard]] LIBNM_LOCAL
    std::vector<std::string> HandleElfEhdr(ElfEhdr,
                                           std::basic_istream<StreamT>&);
#endif
  }
}
