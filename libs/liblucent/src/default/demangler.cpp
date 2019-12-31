//
// Created by tudom on 2019-12-28.
//

#include "../include.hpp"
#include LIBLUCENT_INCLUDE_HEADER_F(lucent.hpp)

#include <boost/core/demangle.hpp>

LIBLUCENT_API
std::string liblucent::Demangle(std::string_view name) {
    return boost::core::demangle(name.data());
}
