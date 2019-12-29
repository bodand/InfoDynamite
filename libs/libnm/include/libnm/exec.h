//
// Created by tudom on 2019-12-29.
//

#pragma once

#include <string>

#include <boost/predef.h>

namespace libnm::arch {
  enum class Endian {
      Little,
      Big
  };

#if BOOST_ARCH_ALPHA
  constexpr auto Name = "Alpha";
  constexpr auto ElfSize = 64u;
  constexpr auto Endianness = Endian::Little;
#elif BOOST_ARCH_ARM
#elif BOOST_ARCH_X86_64
  constexpr auto Name = "x86_64";
  constexpr auto ElfSize = 64u;
  constexpr auto Endinanness = Endian::Little;
#else
#pragma error "Unintelligable architecture. "
#endif
}
