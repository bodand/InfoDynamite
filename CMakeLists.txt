cmake_minimum_required(VERSION 3.10)
project(InfoDynamite)

set(CMAKE_CXX_STANDARD 20)

option(INFO_DYNAMITE_BUILD_SHARED "Build InfoDynamite as shared library" On)
option(INFO_BUILD_TESTS "Build the tests of InfoDynamite and libnm" On)

add_subdirectory(libs)

add_library(dynamite SHARED library.cpp library.h)

if (INFO_BUILD_TESTS)
    add_subdirectory(test)
endif ()
