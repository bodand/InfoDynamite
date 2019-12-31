//
// Created by tudom on 2019-12-29.
//

#pragma once

// System headers
#include <elf.h>

// Dependency headers
#include <boost/endian/conversion.hpp>
#include "magic_enum.hpp"

// Project headers
#include "../include.hpp"
#include LIBNM_INCLUDE_HEADER_N(exec.h)
#include LIBNM_INCLUDE_HEADER_N(_api.hpp)

namespace libnm::detail {
  namespace end = boost::endian;

  template<class ElfEhdr>
  LIBNM_LOCAL
  void FixEndian(ElfEhdr& ehdr) noexcept {
      BOOST_STATIC_ASSERT_MSG(std::is_same_v<std::remove_cv_t<ElfEhdr>, Elf32_Ehdr>
                              || std::is_same_v<std::remove_cv_t<ElfEhdr>, Elf64_Ehdr>,
                              "ElfEhdr is not of appropriate type");

      if (ehdr.e_ident[EI_DATA] == magic_enum::enum_integer(arch::Endinanness))
          return;

      end::endian_reverse_inplace(ehdr.e_type);
      end::endian_reverse_inplace(ehdr.e_machine);
      end::endian_reverse_inplace(ehdr.e_version);
      end::endian_reverse_inplace(ehdr.e_entry);
      end::endian_reverse_inplace(ehdr.e_phoff);
      end::endian_reverse_inplace(ehdr.e_shoff);
      end::endian_reverse_inplace(ehdr.e_flags);
      end::endian_reverse_inplace(ehdr.e_ehsize);
      end::endian_reverse_inplace(ehdr.e_phentsize);
      end::endian_reverse_inplace(ehdr.e_phnum);
      end::endian_reverse_inplace(ehdr.e_shentsize);
      end::endian_reverse_inplace(ehdr.e_shnum);
      end::endian_reverse_inplace(ehdr.e_shstrndx);
  }

  template<class ElfEhdr, class ElfShdr>
  LIBNM_LOCAL
  std::enable_if_t<std::is_same_v<ElfShdr, Elf32_Shdr> || std::is_same_v<ElfShdr, Elf64_Shdr>>
  FixEndian(ElfEhdr& ehdr, ElfShdr& shdr) noexcept {
      BOOST_STATIC_ASSERT_MSG(std::is_same_v<std::remove_cv_t<ElfEhdr>, Elf32_Ehdr>
                              || std::is_same_v<std::remove_cv_t<ElfEhdr>, Elf64_Ehdr>,
                              "ElfEhdr is not of appropriate type");
      BOOST_STATIC_ASSERT_MSG(std::is_same_v<std::remove_cv_t<ElfShdr>, Elf32_Shdr>
                              || std::is_same_v<std::remove_cv_t<ElfShdr>, Elf64_Shdr>,
                              "ElfShdr is not of appropriate type");

      if (ehdr.e_ident[EI_DATA] == magic_enum::enum_integer(arch::Endinanness))
          return;

      end::endian_reverse_inplace(shdr.sh_name);
      end::endian_reverse_inplace(shdr.sh_type);
      end::endian_reverse_inplace(shdr.sh_flags);
      end::endian_reverse_inplace(shdr.sh_addr);
      end::endian_reverse_inplace(shdr.sh_offset);
      end::endian_reverse_inplace(shdr.sh_size);
      end::endian_reverse_inplace(shdr.sh_link);
      end::endian_reverse_inplace(shdr.sh_info);
      end::endian_reverse_inplace(shdr.sh_addralign);
      end::endian_reverse_inplace(shdr.sh_entsize);
  }

  template<class ElfEhdr, class ElfSym>
  LIBNM_LOCAL
  std::enable_if_t<std::is_same_v<ElfSym, Elf32_Sym> || std::is_same_v<ElfSym, Elf64_Sym>>
  FixEndian(ElfEhdr& ehdr, ElfSym& sym) noexcept {
      BOOST_STATIC_ASSERT_MSG(std::is_same_v<std::remove_cv_t<ElfEhdr>, Elf32_Ehdr>
                              || std::is_same_v<std::remove_cv_t<ElfEhdr>, Elf64_Ehdr>,
                              "ElfEhdr is not of appropriate type");
      BOOST_STATIC_ASSERT_MSG(std::is_same_v<std::remove_cv_t<ElfSym>, Elf32_Sym>
                              || std::is_same_v<std::remove_cv_t<ElfSym>, Elf64_Sym>,
                              "ElfSym is not of appropriate type");

      if (ehdr.e_ident[EI_DATA] == magic_enum::enum_integer(arch::Endinanness))
          return;

      end::endian_reverse_inplace(sym.st_name);
      end::endian_reverse_inplace(sym.st_shndx);
      end::endian_reverse_inplace(sym.st_value);
      end::endian_reverse_inplace(sym.st_size);
  }
}
