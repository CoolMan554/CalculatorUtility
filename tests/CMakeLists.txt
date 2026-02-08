cmake_minimum_required(VERSION 3.28)

include(FetchContent)

project(g_tests VERSION 1.0)

add_executable(g_tests
        utest_CalculatorManager.cpp
)

# GoogleTest library
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)

FetchContent_MakeAvailable(
        googletest
)

target_link_libraries(g_tests 
        PRIVATE
        calculator_core 
        gtest_main
)

include(GoogleTest)
gtest_discover_tests(g_tests)
