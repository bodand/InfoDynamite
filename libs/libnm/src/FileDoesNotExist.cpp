//
// Created by tudom on 2019-12-22.
//

#include <utility>

#include "../include/libnm/FileDoesNotExist.hpp"

const char* libnm::file_does_not_exist::what() const noexcept {
    static std::string ret;
    ret = "File `" + _filename + "' does not exist.";
    return ret.c_str();
}

libnm::file_does_not_exist::file_does_not_exist(std::string_view filename)
       : _filename{filename} {}
