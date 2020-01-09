//
// Created by tudom on 2019-12-31.
//

#include <algorithm>

#ifdef _WIN32
#  include <windows.h>
#else
#  include <dlfcn.h>
#endif

#include <libnm/nm.hpp>
#include <liblucent/lucent.hpp>
#include <iostream>
#include <boost/assert.hpp>

#include "include.hpp"
#include INFO_DYNAMITE_INCLUDE(DynamicLibrary.hpp)
#include INFO_DYNAMITE_INCLUDE(DynamicFunction.hpp)
//&!off
#include INFO_DYNAMITE_INCLUDE(exception/NoSuchFunction.hpp)
//&!on

INFO_DYNAMITE_API
info::dynamite::DynamicLibrary::DynamicLibrary(std::string name, bool prefix) noexcept
       : _rawName{std::move(name)},
         _prefix{prefix} {
#ifdef _WIN32
    _lib = LoadLibrary(this->name().c_str());
#else
    _lib = dlopen(this->name().c_str(), RTLD_NOW | RTLD_GLOBAL);
#endif
}

INFO_DYNAMITE_LOCAL
std::string
info::dynamite::DynamicLibrary::prefixName[[nodiscard]]() const noexcept {
    if (_prefix) {
        return LibPrefix + _rawName;
    }
    return _rawName;
}

INFO_DYNAMITE_API
std::string
info::dynamite::DynamicLibrary::elfName[[nodiscard]]() const noexcept {
    return prefixName() + ELFSuffix;
}

INFO_DYNAMITE_API
std::string
info::dynamite::DynamicLibrary::osxName[[nodiscard]]() const noexcept {
    return prefixName() + OSXSuffix;
}

INFO_DYNAMITE_API
std::string
info::dynamite::DynamicLibrary::winName[[nodiscard]]() const noexcept {
    return prefixName() + WinSuffix;
}

INFO_DYNAMITE_API
std::string
info::dynamite::DynamicLibrary::name[[nodiscard]]() const noexcept {
#ifdef _WIN32
    return winName();
#elif defined(__APPLE__)
    return osxName();
#else
    return elfName();
#endif
}

INFO_DYNAMITE_API
std::string&
info::dynamite::DynamicLibrary::rawName[[nodiscard]]() noexcept {
    return _rawName;
}

INFO_DYNAMITE_API
bool&
info::dynamite::DynamicLibrary::prefix[[nodiscard]]() noexcept {
    return _prefix;
}

INFO_DYNAMITE_API
const bool&
info::dynamite::DynamicLibrary::prefix[[nodiscard]]() const noexcept {
    return _prefix;
}

INFO_DYNAMITE_API
const std::string&
info::dynamite::DynamicLibrary::rawName[[nodiscard]]() const noexcept {
    return _rawName;
}

INFO_DYNAMITE_API
void*
info::dynamite::DynamicLibrary::lib[[nodiscard]]() noexcept {
    return _lib;
}

INFO_DYNAMITE_API
const void*
info::dynamite::DynamicLibrary::lib[[nodiscard]]() const noexcept {
    return _lib;
}

INFO_DYNAMITE_API
info::dynamite::DynamicLibrary::~DynamicLibrary() {
    if (_lib == nullptr)
        return;
#ifdef _WIN32
    FreeLibrary((HMODULE) _lib);
#else
    dlclose(_lib);
#endif
}

INFO_DYNAMITE_API
std::vector<std::string>
info::dynamite::DynamicLibrary::functions[[nodiscard]]() const noexcept {
    if (!_cacheFunctions) {
        _cacheFunctions = libnm::GetExports(name());
    }
    return *_cacheFunctions;
}

INFO_DYNAMITE_API
std::vector<std::string>
info::dynamite::DynamicLibrary::demangled[[nodiscard]]() const noexcept {
    if (!_cacheDemangled) {
        auto fs = functions();
        _cacheDemangled = std::vector<std::string>{};

        std::transform(fs.begin(), fs. end(),
                       std::back_inserter(*_cacheDemangled),
                       [](std::string_view mangled) {
                         return liblucent::Demangle(mangled);
                       });
    }
    return *_cacheDemangled;
}

INFO_DYNAMITE_API
info::dynamite::DynamicFunction
info::dynamite::DynamicLibrary::getFunction[[nodiscard]](std::string_view fname) const {
    auto fs = functions();
    auto ds = this->demangled();

    auto position = ([&] {
      decltype(auto) pos = std::find(ds.begin(), ds.end(), fname);

      if (pos == ds.end())
          throw no_such_function{fname.data()};

      return std::distance(ds.begin(), pos);
    })();

    BOOST_ASSERT(static_cast<unsigned long long>(position) < ds.size());

    return {
           loadFunction(fs[static_cast<std::size_t>(position)]),
           ds[static_cast<std::size_t>(position)]
    };
}

INFO_DYNAMITE_LOCAL
info::dynamite::AbstractFunction
info::dynamite::DynamicLibrary::loadFunction[[nodiscard]](std::string_view name) const {
    BOOST_ASSERT(_lib != nullptr);

#ifdef _WIN32
    return reinterpret_cast<AbstractFunction>(GetProcAddress((HMODULE) _lib, name.data()));
#else
    return reinterpret_cast<AbstractFunction>(dlsym(_lib, name.data()));
#endif
}
