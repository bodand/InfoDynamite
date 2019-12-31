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

#include "include.hpp"
#include INFO_DYNAMITE_INCLUDE(DynamicLibrary.hpp)

info::dynamite::DynamicLibrary::DynamicLibrary(std::string name, bool prefix) noexcept
       : _rawName{std::move(name)},
         _prefix{prefix} {
#ifdef _WIN32
    _lib = LoadLibrary(this->name());
#else
    _lib = dlopen(this->name().c_str(), RTLD_LAZY | RTLD_GLOBAL);
#endif
}

std::string info::dynamite::DynamicLibrary::prefixName() const noexcept {
    if (_prefix) {
        return LibPrefix + _rawName;
    }
    return _rawName;
}

std::string info::dynamite::DynamicLibrary::elfName() const noexcept {
    return prefixName() + ELFSuffix;
}

std::string info::dynamite::DynamicLibrary::osxName() const noexcept {
    return prefixName() + OSXSuffix;
}

std::string info::dynamite::DynamicLibrary::winName() const noexcept {
    return prefixName() + WinSuffix;
}

std::string info::dynamite::DynamicLibrary::name() const noexcept {
#ifdef _WIN32
    return winName();
#elif defined(__APPLE__)
    return osxName();
#else
    return elfName();
#endif
}

std::string& info::dynamite::DynamicLibrary::rawName() noexcept {
    return _rawName;
}

bool& info::dynamite::DynamicLibrary::prefix() noexcept {
    return _prefix;
}

const bool& info::dynamite::DynamicLibrary::prefix() const noexcept {
    return _prefix;
}

const std::string& info::dynamite::DynamicLibrary::rawName() const noexcept {
    return _rawName;
}

void* info::dynamite::DynamicLibrary::lib() noexcept {
    return _lib;
}

const void* info::dynamite::DynamicLibrary::lib() const noexcept {
    return _lib;
}

info::dynamite::DynamicLibrary::~DynamicLibrary() {
    if (_lib == nullptr)
        return;
#ifdef _WIN32
    //todo
#else
    dlclose(_lib);
#endif
}

std::vector<std::string> info::dynamite::DynamicLibrary::functions() const noexcept {
    if (!_cacheFunctions) {
        _cacheFunctions = libnm::GetExports(name());
    }
    return *_cacheFunctions;
}

std::vector<std::string> info::dynamite::DynamicLibrary::demangled() const noexcept {
    if (!_cacheDemangled) {
        auto& fs = *_cacheFunctions;
        _cacheDemangled = std::vector<std::string>{};

        std::transform(fs.begin(), fs.end(), _cacheDemangled->begin(), [](std::string_view mangled) {
          return liblucent::Demangle(mangled);
        });
    }
    return *_cacheDemangled;
}

