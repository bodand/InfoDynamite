cmake_minimum_required(VERSION 3.10)

project(InfoDynamiteTests)

find_package(Boost REQUIRED)

add_subdirectory(dummy)

add_subdirectory(dynamite)
add_subdirectory(libs)
