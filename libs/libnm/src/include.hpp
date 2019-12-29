//
// Created by tudom on 2019-12-21.
//

#pragma once

#include <boost/preprocessor/stringize.hpp>

#define LIBNM_INCLUDE_HEADER(header) \
    BOOST_PP_STRINGIZE(../include/libnm/header)

