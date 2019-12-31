//
// Created by tudom on 2019-12-28.
//

#pragma once

#include <string>
#include <string_view>
#include "_api.hpp"

/**
 * Library for the in-house demangler function.
 * Delegates the demangling to implementation specific functions or Boost.
 *
 * > Definition of lucent
 * > 1 : glowing with light : luminous
 * > 2 : marked by clarity or translucence : clear
 * > - [Merriam-Webster dictionary](https://www.merriam-webster.com/dictionary/lucent)
 *
 * \version 1.0.0
 */
namespace liblucent {
  /**
   * Produces a demangled name from the supplied mangled name.
   * Delegates the work to the standard library's built-in demangler function
   * on stdlib, libc++ and MSVC's STL, if something other than these is used
   * it falls back to Boost.Core's demangle.
   *
   * \param name The mangled name to demangle
   *
   * \return The demangled name if the process is successful, otherwise the input
   *          string.
   */
  [[nodiscard]] LIBLUCENT_API
  std::string Demangle(std::string_view);

  namespace detail {
    [[nodiscard]] LIBLUCENT_LOCAL
    bool balanced_parens(std::string_view);
  }
}
