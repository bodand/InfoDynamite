//
// Created by tudom on 2019-12-21.
//

#include <filesystem> //until GCC 9.3.0 is available on MSYS I cannot compile with clang
#include "../include/libnm/FileNotObject.hpp"
#include "../include/libnm/FileDoesNotExist.hpp"

#include "include.hpp"

#include LIBNM_INCLUDE_HEADER(nm.hpp)

std::vector<std::string> libnm::GetExports(std::string_view filename) {
    if (!std::filesystem::exists(filename)) {
        throw file_does_not_exist{filename};
    }

    if (!IsSharedObject(filename)) {
        throw file_not_object{filename};
    }

    return detail::ListExports(filename);
}

