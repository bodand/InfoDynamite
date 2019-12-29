//
// Created by tudom on 2019-12-21.
//

#pragma once

#include <string>
#include <string_view>
#include <vector>

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
  [[nodiscard]]
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
  [[nodiscard]]
  bool IsSharedObject(std::string_view) noexcept;

  namespace detail {
    std::vector<std::string> ListExports(std::string_view) noexcept;
  }
}
