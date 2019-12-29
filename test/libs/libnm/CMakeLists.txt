project(InfoDynamiteTest_libnm)

enable_testing()

set(libnm_TEST_HEADERS
        Test_Tests.hpp
        Test_GetExports.hpp
        )

foreach (case ${libnm_TEST_HEADERS})
    set(libnm_TEST_CASES "${libnm_TEST_CASES}
#include \"${case}\"")
endforeach ()

configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp.in"
        "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
)

add_executable(nm_t main.cpp)

add_dependencies(nm_t dummy)

target_link_libraries(nm_t
        nm
        )

add_test(TestSuite_libnm
        "nm_t -v"
        )
