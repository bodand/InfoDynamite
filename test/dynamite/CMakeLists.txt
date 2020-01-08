project(InfoDynamiteTest_Dynamite)

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

enable_testing()

set(INFO_DYNAMITE_TEST_HEADERS
        Test_Tests.hpp
        Test_DynamicLibrary.hpp
        Test_DynamicFunction.hpp
        )

foreach (case ${INFO_DYNAMITE_TEST_HEADERS})
    set(INFO_DYNAMITE_TEST_CASES "${INFO_DYNAMITE_TEST_CASES}
#include \"${case}\"")
endforeach ()

configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp.in"
        "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
)

add_executable(explode main.cpp)
add_dependencies(explode dummy)

target_link_libraries(explode
        dynamite
        )

add_test(TestSuiteDynamite
        "explode -v"
        )

add_custom_command(TARGET explode POST_BUILD
        COMMAND ${EXEC_PFX} cmake -E copy ${CMAKE_BINARY_DIR}/libdynamite.${EXT} ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Copying dynamite shared object for InfoDynamite tests"
        )
