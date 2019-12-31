cmake_minimum_required(VERSION 3.10)

project(libnm
        VERSION 1.0.0
        LANGUAGES CXX
        )
set(CMAKE_CXX_STANDARD 20)

option(LIBNM_BUILD_SHARED "Build libnm as a dynamic library" Off)

if (LIBNM_BUILD_SHARED)
    set(LIBNM_LIBRARY_TYPE SHARED)
else ()
    set(LIBNM_LIBRARY_TYPE STATIC)
endif ()

# Init Dependencies
find_package(Boost REQUIRED filesystem)

# Check which platform we on
if (WIN32)
    set(LIBNM_OS_DEPENDENT_SOURCE_DIR windows)
else ()
    set(LIBNM_OS_DEPENDENT_SOURCE_DIR elf)
endif ()

add_library(nm ${LIBNM_LIBRARY_TYPE}
        src/nm.cpp
        src/exception/FileNotObject.cpp
        src/exception/FileDoesNotExist.cpp
        src/exception/CorruptedELFObject.cpp
        src/${LIBNM_OS_DEPENDENT_SOURCE_DIR}/nm.cpp
        )

# Symbol hiding
if (LIBNM_BUILD_SHARED)
    message(STATUS "Building libnm as shared library")
    if (WIN32)
        if (("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
                OR ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang"))
            target_link_options(lucent
                    PUBLIC
                    -Wl,--exclude-all-symbols
                    )
        endif ()
    endif ()
    add_definitions(-DLIBNM_DLL -DLIBNM_BUILD)
endif ()


# Add Dependencies
add_dependencies(nm magic_enum)

get_target_property(MAGIC_ENUM_INCLUDE_DIRS magic_enum::magic_enum INTERFACE_INCLUDE_DIRECTORIES)

target_include_directories(nm
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>

        PRIVATE
        ${Boost_INCLUDE_DIRS}
        ${MAGIC_ENUM_INCLUDE_DIRS}
        ${SPROUT_INCLUDE_DIR}
        src
        )

target_link_directories(nm
        PUBLIC
        ${Boost_LIBRARY_DIRS}
        )

if (WIN32)
    target_link_libraries(nm
            ${Boost_LIBRARIES}
            imagehlp
            )
else ()
    target_link_libraries(nm
            ${Boost_LIBRARIES}
            )
endif ()
