//
// Created by tudom on 2019-12-22.
//

#include "include.hpp"
//&!off
#include LIBNM_INCLUDE_HEADER_N(exception/FileNotObject.hpp)
//&!on

const char* libnm::file_not_object::what() const noexcept {
    static std::string ret;
    ret = "File `" + _filename + "' is not a shared object.";
    return ret.c_str();
}

libnm::file_not_object::file_not_object(std::string_view filename)
       : _filename{filename} {}

