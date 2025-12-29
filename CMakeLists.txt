cmake_minimum_required(VERSION 3.10)

include(FetchContent)

project(calculator_utility VERSION 1.0)

add_executable(calculator_utility
        main.cpp            
)

# C++ standard (add --std=c++17)
target_compile_features(calculator_utility PUBLIC cxx_std_17)

# 
set_target_properties(calculator_utility PROPERTIES
    CXX_STANDARD_REQUIRED YES #lowering the standard NO
    CXX_EXTENSIONS NO #banning GNU-CLANG extensions
)

# Compiler warnings
target_compile_options(calculator_utility PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)

FetchContent_Declare(
        math
        GIT_REPOSITORY https://github.com/CoolMan554/LibCalculatorUtility.git
        GIT_TAG v0.1.2
)

FetchContent_MakeAvailable(
        math
)

target_link_libraries(calculator_utility
        PRIVATE
        math
)

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
                essage(WARNING
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