cmake_minimum_required(VERSION 3.10)
project(InfoDynamite)

set(CMAKE_CXX_STANDARD 20)

option(INFO_DYNAMITE_BUILD_SHARED "Build InfoDynamite as shared library" On)
option(INFO_BUILD_TESTS "Build the tests of InfoDynamite and libnm" On)

include(cmake/Dependencies.cmake)
GetDependencies()

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options(
            -Wall
            -Wextra
            -Wsign-compare
            -Wswitch-enum
            -Wuninitialized
            -Wunused
            -Wno-unknown-pragmas
            -Wcast-qual
            -Wcast-align
            -Wabstract-vbase-init
            -Warray-bounds-pointer-arithmetic
            -Wassign-enum
            -Wconditional-uninitialized
            -Wconsumed
            -Wdeprecated-implementations
            -Wdocumentation-deprecated-sync
            -Wnon-virtual-dtor
            -Wheader-hygiene
            -Winfinite-recursion
            -Wkeyword-macro
            -Wloop-analysis
            -Wmissing-braces
            -Wmove
            -Wnewline-eof
            -Wover-aligned
            -Wredundant-parens
            -Wreorder
            -Wreserved-id-macro
            -Wsign-conversion
            -Wsigned-enum-bitfield
            -Wsometimes-uninitialized
            -Wtautological-overlap-compare
            -Wthread-safety
            -Wundefined-internal-type
            -Wundefined-reinterpret-cast
            -Wunneeded-internal-declaration
            -Wunreachable-code-aggressive
            -Wunreachable-code-loop-increment
            -Wunused-const-variable
            -Wunused-exception-parameter
            -Wunused-label
            -Wunused-parameter
            -Wunused-private-field
            -Wunused-lambda-capture
            -Wunused-template
            -Wunused-variable
            -Wused-but-marked-unused
            -pedantic
    )
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options(
            -Wall
            -Wextra
            -Wswitch-enum
            -Wuninitialized
            -Wunused
            -Wno-unknown-pragmas
            -Wsuggest-attribute=pure
            -Wsuggest-attribute=const
            -Wsuggest-attribute=cold
            -Wsuggest-final-types
            -Wsuggest-final-methods
            -Wduplicated-branches
            -Wtrampolines
            -Wplacement-new=2
            -Wcast-qual
            -Wcast-align
            -Wlogical-op
            -Wredundant-decls
            -pedantic
    )
endif ()

add_subdirectory(libs)

add_library(dynamite SHARED library.cpp library.h)

if (INFO_BUILD_TESTS)
    add_subdirectory(test)
endif ()
