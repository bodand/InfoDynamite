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
find_package(Boost REQUIRED regex)

# Check which platform we on
if (WIN32)
    set(LIBNM_OS_DEPENDENT_SOURCE_DIR windows)
else ()
    set(LIBNM_OS_DEPENDENT_SOURCE_DIR elf)
endif ()

add_library(nm ${LIBNM_LIBRARY_TYPE}
        src/nm.cpp
        src/FileNotObject.cpp
        src/FileDoesNotExist.cpp
        src/${LIBNM_OS_DEPENDENT_SOURCE_DIR}/nm.cpp
        )

# Add Dependencies
target_include_directories(nm
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>

        PRIVATE
        ${Boost_INCLUDE_DIRS}
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
