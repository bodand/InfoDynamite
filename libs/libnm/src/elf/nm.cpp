//
// Created by tudom on 2019-12-22.
//

#include <cstring>
#include <fstream>
#include "libnm/nm.hpp"

bool libnm::IsSharedObject(std::string_view file) noexcept {
    char magic[4];
    std::ifstream str(file.data());
    str.read(magic, 4);
    return std::strncmp(magic, "\177ELF", 4);
}

std::vector<std::string> libnm::detail::ListExports(std::string_view file) noexcept {
    return {};
}
