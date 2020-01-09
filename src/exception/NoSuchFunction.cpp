//
// Created by tudom on 2019-12-31.
//

#include <utility>

#include "../include.hpp"
//&!off
#include INFO_DYNAMITE_INCLUDE_N(exception/NoSuchFunction.hpp)
//&!on

INFO_DYNAMITE_API
const char*
info::dynamite::no_such_function::what[[nodiscard]]() const noexcept {
    static std::string ret;
    ret = "Requested function `" + _function + "` not found.";
    return ret.c_str();
}

INFO_DYNAMITE_API
info::dynamite::no_such_function::no_such_function(std::string function) noexcept
       : _function{std::move(function)} {}
