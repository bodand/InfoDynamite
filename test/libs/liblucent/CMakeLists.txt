project(InfoDynamiteTest_liblucent)

enable_testing()

set(liblucent_TEST_HEADERS
        Test_Tests.hpp
        Test_Demangle.hpp
        )

foreach (case ${liblucent_TEST_HEADERS})
    set(liblucent_TEST_CASES "${liblucent_TEST_CASES}
#include \"${case}\"")
endforeach ()

configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp.in"
        "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
)

add_executable(lucent_t main.cpp)

target_link_libraries(lucent_t
        lucent
        )

add_test(TestSuite_liblucent
        "lucent_t -v"
        )
