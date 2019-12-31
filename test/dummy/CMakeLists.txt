project(Dummy)

add_library(dummy SHARED dummy.cpp)

if (WIN32)
    set(EXT dll)
    set(EXEC_PFX cmd /c)
    if (("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
            OR ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang"))
        target_link_options(dummy
                PUBLIC
                -Wl,--exclude-all-symbols
                )
    endif ()
    add_compile_definitions(INFO_BUILD_DLL)
elseif (__APPLE__)
    set(EXT dylib)
else ()
    set(EXT so)
endif ()

add_custom_command(TARGET dummy POST_BUILD
        COMMAND ${EXEC_PFX} cmake -E copy ${CMAKE_CURRENT_BINARY_DIR}/libdummy.${EXT} ${CMAKE_BINARY_DIR}/test/dynamite/
        COMMENT "Copying dummy library for InfoDynamite tests"
        )

add_custom_command(TARGET dummy POST_BUILD
        COMMAND ${EXEC_PFX} cmake -E copy ${CMAKE_CURRENT_BINARY_DIR}/libdummy.${EXT} ${CMAKE_BINARY_DIR}/test/libs/libnm/
        COMMENT "Copying dummy library for libnm tests"
        )
