//
// Created by tudom on 2019-12-31.
//

#pragma once

#include <boost/preprocessor/stringize.hpp>

#define INFO_DYNAMITE_INCLUDE(header) \
    BOOST_PP_STRINGIZE(../include/info/dynamite/header)

#define INFO_DYNAMITE_INCLUDE_N(header) \
    BOOST_PP_STRINGIZE(../../include/info/dynamite/header)
