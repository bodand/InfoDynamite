cmake_minimum_required(VERSION 3.14)
project(InfoDynamite)

set(CMAKE_CXX_STANDARD 20)

option(INFO_DYNAMITE_BUILD_SHARED "Build InfoDynamite as shared library" On)
option(INFO_BUILD_TESTS "Build the tests of InfoDynamite and libnm" On)

if (INFO_DYNAMITE_BUILD_SHARED)
    set(INFO_DYNAMITE_LIBRARY_TYPE SHARED)
else ()
    set(INFO_DYNAMITE_LIBRARY_TYPE STATIC)
endif ()

set(CMAKE_SKIP_RPATH FALSE)
set(CMAKE_BUILD_RPATH "$ORIGIN:${CMAKE_BINARY_DIR}:${CMAKE_BUILD_RPATH}")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG")

# Get the dependencies
include(cmake/Dependencies.cmake)
GetDependencies()

# Add non-default compiler warnings
include(cmake/Warnings.cmake)

# Add dependencies
add_subdirectory(libs)
include(libs/DependencyInclude.cmake)

# Register library
add_library(dynamite ${INFO_DYNAMITE_LIBRARY_TYPE}
        src/DynamicLibrary.cpp
        src/DynamicFunction.cpp
        src/exception/NoSuchFunction.cpp
        )

# Symbol management
if (INFO_DYNAMITE_BUILD_SHARED)
    message(STATUS "Building InfoDynamite as shared library")
    if (WIN32)
        if (("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
                OR ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang"))
            target_link_options(dynamite
                    PUBLIC
                    -Wl,--exclude-all-symbols
                    )
        endif ()
    endif ()

    add_definitions(-DINFO_DYNAMITE_DLL -DINFO_DYNAMITE_BUILD_DLL)
endif ()
set_target_properties(dynamite PROPERTIES POSITION_INDEPENDENT_CODE ON)

# Set includes
target_include_directories(dynamite
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>

        PRIVATE
        ${LIBNM_INCLUDE_DIR}
        ${LIBLUCENT_INCLUDE_DIR}
        src
        )

# Link settings
set(DYNAMITE_LINK_LIBRARIES nm lucent)

if (WIN32)
    set(DYNAMITE_LINK_LIBRARIES ${DYNAMITE_LINK_LIBRARIES} kernel32)
else ()
    set(DYNAMITE_LINK_LIBRARIES ${DYNAMITE_LINK_LIBRARIES} dl)
endif ()

target_link_libraries(dynamite ${DYNAMITE_LINK_LIBRARIES})

# Testing setup
if (INFO_BUILD_TESTS)
    add_subdirectory(test)
endif ()
