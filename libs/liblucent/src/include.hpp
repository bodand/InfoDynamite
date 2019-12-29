//
// Created by tudom on 2019-12-28.
//

#pragma once

#include <boost/preprocessor/stringize.hpp>

#define LIBLUCENT_INCLUDE_HEADER(header) \
    BOOST_PP_STRINGIZE(../include/liblucent/header)

#define LIBLUCENT_INCLUDE_HEADER_F(header) \
    BOOST_PP_STRINGIZE(../../include/liblucent/header)

