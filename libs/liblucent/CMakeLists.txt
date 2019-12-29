cmake_minimum_required(VERSION 3.10)

project(liblucent
        VERSION 1.0.0
        LANGUAGES CXX
        )
include(functions.cmake)

option(LIBLUCENT_BUILD_SHARED "Build liblucent as a dynamic library" Off)

if (LIBLUCENT_BUILD_SHARED)
    set(LIBLUCENT_LIBRARY_TYPE SHARED)
else ()
    set(LIBLUCENT_LIBRARY_TYPE STATIC)
endif ()

# Init Dependencies
find_package(Boost REQUIRED regex)

# Check stdlib implementation
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    set(LIBLUCENT_STDLIB_DEPENDENT_SOURCE_DIR msvc)
    set(LIBLUCENT_LIBS ${LIBLUCENT_LIBS};dbghelp)
    add_compile_definitions(LIBLUCENT_MSABI_MANGING_SCHEME)

elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    set(LIBLUCENT_STDLIB_DEPENDENT_SOURCE_DIR stdlib)

elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
    is_libcxx(IS_LIBCXX)
    is_msvc_stl(IS_MSVC_STL)
    is_libstdcxx(IS_LIBSTDCXX)

    if (${IS_LIBCXX}) # LLVM libc++
        set(LIBLUCENT_STDLIB_DEPENDENT_SOURCE_DIR stdlib)
        set(LIBLUCENT_LIBS ${LIBLUCENT_LIBS};cxxabi)

    elseif (${IS_MSVC_STL}) # MSVC STL
        set(LIBLUCENT_STDLIB_DEPENDENT_SOURCE_DIR msvc)
        set(LIBLUCENT_LIBS ${LIBLUCENT_LIBS};dbghelp)
        add_compile_definitions(LIBLUCENT_MSABI_MANGING_SCHEME)

    elseif (${IS_LIBSTDCXX}) # GNU libstdc++
        set(LIBLUCENT_STDLIB_DEPENDENT_SOURCE_DIR stdlib)

    else ()
        set(LIBLUCENT_STDLIB_DEPENDENT_SOURCE_DIR default)
    endif ()
else ()
    set(LIBLUCENT_STDLIB_DEPENDENT_SOURCE_DIR default)
endif ()

# Register targets
add_library(lucent ${LIBLUCENT_LIBRARY_TYPE}
        src/lucent.cpp
        src/${LIBLUCENT_STDLIB_DEPENDENT_SOURCE_DIR}/demangler.cpp
        )

# Add Dependencies
target_include_directories(lucent
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>

        PRIVATE
        ${Boost_INCLUDE_DIRS}
        src
        )

target_link_directories(lucent
        PUBLIC
        ${Boost_LIBRARY_DIRS}
        )

target_link_libraries(lucent
        PRIVATE
        ${Boost_LIBRARIES}
        ${LIBLUCENT_LIBS}
        )
