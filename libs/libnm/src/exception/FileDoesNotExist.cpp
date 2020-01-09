//
// Created by tudom on 2019-12-22.
//

#include <utility>

#include "include.hpp"
//&!off
#include LIBNM_INCLUDE_HEADER_N(exception/FileDoesNotExist.hpp)
//&!on

LIBNM_API
const char* libnm::file_does_not_exist::what() const noexcept {
    static std::string ret;
    ret = "File `" + _filename + "' does not exist.";
    return ret.c_str();
}

LIBNM_API
libnm::file_does_not_exist::file_does_not_exist(std::string_view filename)
       : _filename{filename} {}
