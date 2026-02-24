cmake_minimum_required(VERSION 3.28)

include(FetchContent)

project(calculator_utility VERSION 1.0)

add_library(calculator_core
        src/Application.cpp
        src/Calculator.cpp
        src/Checker.cpp
        src/CliParser.cpp
        src/JsonInputParser.cpp
        src/Printer.cpp
        src/Logger.cpp
        src/PostgreSqlDB.cpp
)

target_include_directories(calculator_core 
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        /usr/include/postgresql
)

# C++ standard (add --std=c++17)
target_compile_features(calculator_core PUBLIC cxx_std_17)

set_target_properties(calculator_core PROPERTIES
    CXX_STANDARD_REQUIRED YES #lowering the standard NO
    CXX_EXTENSIONS NO #banning GNU-CLANG extensions
)

# Compiler warnings
target_compile_options(calculator_core PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

# Dependencies

# static library
FetchContent_Declare(
        library_math
        GIT_REPOSITORY https://github.com/CoolMan554/LibCalculatorUtility.git
        GIT_TAG v.0.1.4
)

FetchContent_MakeAvailable(
        library_math
)

# library json
FetchContent_Declare(json 
        URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
)

FetchContent_MakeAvailable(
        json
)

# library spdlog
FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.x
)

FetchContent_MakeAvailable(
        spdlog
)

target_link_libraries(calculator_core 
        PUBLIC
        library_math
        nlohmann_json::nlohmann_json
        spdlog::spdlog
        pq
)

add_executable(calculator_utility
    src/main.cpp
)

target_link_libraries(calculator_utility 
        PRIVATE
        calculator_core
)

# Tests
enable_testing()
add_subdirectory(tests)

# install
install(TARGETS calculator_utility
        ARCHIVE DESTINATION /usr/local/lib/
        LIBRARY DESTINATION /usr/local/lib/
        RUNTIME DESTINATION /usr/local/bin/
)

#clang-format

option(ENABLE_CLANG_FORMAT "Run clang-format" OFF)

if(ENABLE_CLANG_FORMAT)
        find_program(CLANG_FORMAT_EXE "clang-format")
        get_target_property(target_sources calculator_utility SOURCES)
        if(CLANG_FORMAT_EXE)
                add_custom_target(format 
                COMMENT "Formatting files with clang-format..." 
                COMMAND ${CLANG_FORMAT_EXE} -i ${target_sources}
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                )
                message(STATUS "Added 'format' target")
        else() 
                message(WARNING
                "clang-format not found - format target unavailable") 
        endif()
endif()

#clang-tidy

option(ENABLE_CLANG_TIDY "Run clang-tidy" OFF)

if(ENABLE_CLANG_TIDY)
        find_program(CLANG_TIDY_EXE "clang-tidy")
        if(CLANG_TIDY_EXE)
                set_target_properties(calculator_utility PROPERTIES 
                        CXX_CLANG_TIDY
                        "${CLANG_TIDY_EXE};-p=${CMAKE_BINARY_DIR}")
        else()
                message(WARNING "clang-tidy not found!")
        endif()
endif()