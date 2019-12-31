//
// Created by tudom on 2019-12-21.
//

// Dependency headers
#include <boost/filesystem.hpp> //libstdc++ filesystem is broken
//but we use boost anyway so whatever
// Project headers
#include "include.hpp"
#include LIBNM_INCLUDE_HEADER(nm.hpp)
//&!off
#include LIBNM_INCLUDE_HEADER(exception/FileNotObject.hpp)
#include LIBNM_INCLUDE_HEADER(exception/FileDoesNotExist.hpp)
//&!on

LIBNM_API
std::vector<std::string> libnm::GetExports(std::string_view filename) {
    if (!boost::filesystem::exists(filename.data())) {
        throw file_does_not_exist{filename};
    }

    if (!IsSharedObject(filename)) {
        throw file_not_object{filename};
    }

    return detail::ListExports(filename);
}

