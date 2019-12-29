project(Dummy)

add_library(dummy SHARED dummy.cpp)

if (WIN32)
    set(EXT dll)
    set(EXEC_PFX cmd /c)
    if (("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
            OR ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang"))
        message(STATUS "GCC/Clang on Windows")
        target_link_options(dummy
                PUBLIC
                -Wl,--exclude-all-symbols
                )
    endif ()
elseif (__APPLE__)
    set(EXT dylib)
    set(EXEC_PFX)
else ()
    set(EXT so)
    set(EXEC_PFX)
endif ()

add_compile_definitions(INFO_BUILD_DLL)

add_custom_command(TARGET dummy POST_BUILD
        COMMAND ${EXEC_PFX} cmake -E copy ${CMAKE_CURRENT_BINARY_DIR}/libdummy.${EXT} ${CMAKE_BINARY_DIR}/test/dynamite/
        COMMENT "Copying dummy library for InfoDynamite tests"
        )

add_custom_command(TARGET dummy POST_BUILD
        COMMAND ${EXEC_PFX} cmake -E copy ${CMAKE_CURRENT_BINARY_DIR}/libdummy.${EXT} ${CMAKE_BINARY_DIR}/test/libs/libnm/
        COMMENT "Copying dummy library for libnm tests"
        )
