project(InfoDynamiteTest_Dynamite)

enable_testing()

set(INFO_DYNAMITE_TEST_HEADERS
        Test_Tests.hpp
        Test_DynamicLibrary.hpp
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
