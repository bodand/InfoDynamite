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
#include "FunctionTypes.hpp"

namespace info::dynamite {
  struct INFO_DYNAMITE_API DynamicFunction;

  struct INFO_DYNAMITE_API DynamicLibrary {
      // functions
      std::string name[[nodiscard]]() const noexcept;
      std::string winName[[nodiscard]]() const noexcept;
      std::string osxName[[nodiscard]]() const noexcept;
      std::string elfName[[nodiscard]]() const noexcept;

      std::vector <std::string> functions[[nodiscard]]() const noexcept;
      std::vector <std::string> demangled[[nodiscard]]() const noexcept;

      DynamicFunction getFunction[[nodiscard]](std::string_view) const;

      // accessors
      std::string& rawName[[nodiscard]]() noexcept;
      const std::string& rawName[[nodiscard]]() const noexcept;

      bool& prefix[[nodiscard]]() noexcept;
      const bool& prefix[[nodiscard]]() const noexcept;

      void* lib[[nodiscard]]() noexcept;
      const void* lib[[nodiscard]]() const noexcept;

      // constructors
      explicit DynamicLibrary(std::string, bool = true) noexcept;

      // destructor
      virtual ~DynamicLibrary();
  private:
      std::string _rawName;
      bool _prefix;
      void* _lib;

      mutable std::optional <std::vector<std::string>> _cacheFunctions;
      mutable std::optional <std::vector<std::string>> _cacheDemangled;

      INFO_DYNAMITE_LOCAL
      std::string prefixName[[nodiscard]]() const noexcept;

      INFO_DYNAMITE_LOCAL
      AbstractFunction loadFunction[[nodiscard]](std::string_view) const;

      INFO_DYNAMITE_LOCAL
      static constexpr const auto LibPrefix = "lib";
      INFO_DYNAMITE_LOCAL
      static constexpr const auto WinSuffix = ".dll";
      INFO_DYNAMITE_LOCAL
      static constexpr const auto OSXSuffix = ".dylib";
      INFO_DYNAMITE_LOCAL
      static constexpr const auto ELFSuffix = ".so";
  };
}
