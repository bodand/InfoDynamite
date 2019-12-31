//
// Created by tudom on 2019-12-29.
//

#pragma once

#include <string>

#include <boost/predef.h>
#include "magic_enum.hpp"
#include "_api.hpp"

namespace libnm::arch {
  enum class LIBNM_LOCAL Endian {
      Little = 1,
      Big = 2
  };

  // note: please keep the list in alphabetical order
#if BOOST_ARCH_ALPHA
#  pragma message "[libnm] Detected Alpha architecture"
  constexpr auto Name = "Alpha";
  constexpr auto ElfSize = 64u;
  constexpr auto Endianness = Endian::Little;
#elif BOOST_ARCH_ARM
#  if defined(_M_ARM64) || defined(__arm64) \
      || defined(__aarch64__) || defined(__AARCH64EL__)
#    pragma message "[libnm] Detected ARM 64-bit architecture"
  constexpr auto Name = "ARM64";
  constexpr auto ElfSize = 64u;
  constexpr auto Endinanness = Endian::Little;
#  else
#    pragma message "[libnm] Detected ARM 32-bit architecture"
  constexpr auto Name = "ARM";
  constexpr auto ElfSize = 32u;
  constexpr auto Endinanness = Endian::Little;
#  endif
#elif BOOST_ARCH_MIPS
#  pragma message "[libnm] Detectec MIPS architecutre"
  constexpr auto Name = "MIPS";
  constexpr auto ElfSize = 64u;
#  if defined(__MIPSEB__)
  constexpr auto Endinanness = Endian::Big;
#  else
  constexpr auto Endinanness = Endian::Little;
#  endif
#elif BOOST_ARCH_PARISC
#  pragma message "[libnm] Detected HP/PA RISC architecture"
  constexpr auto Name = "HP/PA RISC";
  constexpr auto ElfSize = 32u;
  constexpr auto Endinanness = Endian::Big;
#elif BOOST_ARCH_PPC
#  pragma message "[libnm] Detectec PowerPC architecutre"
  constexpr auto Name = "PowerPC";
  constexpr auto ElfSize = 32u;
  constexpr auto Endinanness = Endian::Big;
#elif BOOST_ARCH_SH
#  pragma message "[libnm] Detectec SuperH architecutre"
  constexpr auto Name = "SuperH";
  constexpr auto ElfSize = 32u;
#  ifdef __LITTLE_ENDIAN__
  constexpr auto Endinanness = Endian::Little;
#  else
  constexpr auto Endinanness = Endian::Big;
#  endif
#elif BOOST_ARCH_SPARC
#  pragma message "[libnm] Detectec SPARC architecutre"
  constexpr auto Name = "SPARC";
  constexpr auto ElfSize = 64u;
  constexpr auto Endinanness = Endian::Big;
#elif BOOST_ARCH_X86_32
#  pragma message "[libnm] Detected x86 32-bit architecture"
  constexpr auto Name = "x86";
  constexpr auto ElfSize = 32u;
  constexpr auto Endinanness = Endian::Little;
#elif BOOST_ARCH_X86_64
#  pragma message "[libnm] Detected x86 64-bit architecture"
  LIBNM_API constexpr auto Name = "x86_64";
  LIBNM_API constexpr auto ElfSize = 64u;
  LIBNM_API constexpr auto Endinanness = Endian::Little;
#else
#pragma error "[libnm] Unintelligable architecture."
#endif
}
