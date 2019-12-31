//
// Created by tudom on 2019-12-31.
//

#pragma once

// std headers
#include <string>
#include <vector>
#include <optional>

// project headers
#include "_api.hpp"

namespace info::dynamite {
  struct INFO_DYNAMITE_API DynamicLibrary {
      // functions
      [[nodiscard]]
      std::string name() const noexcept;
      [[nodiscard]]
      std::string winName() const noexcept;
      [[nodiscard]]
      std::string osxName() const noexcept;
      [[nodiscard]]
      std::string elfName() const noexcept;

      [[nodiscard]]
      std::vector<std::string> functions() const noexcept;
      [[nodiscard]]
      std::vector<std::string> demangled() const noexcept;

      // accessors
      [[nodiscard]]
      std::string& rawName() noexcept;
      [[nodiscard]]
      const std::string& rawName() const noexcept;

      [[nodiscard]]
      bool& prefix() noexcept;
      [[nodiscard]]
      const bool& prefix() const noexcept;

      [[nodiscard]]
      void* lib() noexcept;
      [[nodiscard]]
      const void* lib() const noexcept;

      // constructors
      explicit DynamicLibrary(std::string, bool = true) noexcept;

      // destructor
      virtual ~DynamicLibrary();
  private:
      std::string _rawName;
      bool _prefix;
      void* _lib;

      mutable std::optional<std::vector<std::string>> _cacheFunctions;
      mutable std::optional<std::vector<std::string>> _cacheDemangled;

      [[nodiscard]]
      std::string prefixName() const noexcept;

      static constexpr const auto LibPrefix = "lib";
      static constexpr const auto WinSuffix = ".dll";
      static constexpr const auto OSXSuffix = ".dylib";
      static constexpr const auto ELFSuffix = ".so";
  };
}
