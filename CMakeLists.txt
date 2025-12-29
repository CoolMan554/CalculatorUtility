cmake_minimum_required(VERSION 3.5)

include(FetchContent)

project(calculator_utility)

FetchContent_Declare(
        libMath
        GIT_REPOSITORY https://github.com/CoolMan554/LibCalculatorUtility.git
        GIT_TAG v0.1.1
)

FetchContent_MakeAvailable(
        libMath
)

add_executable(calculator_utility
        main.cpp            
)

target_link_libraries(calculator_utility
        PRIVATE
        libMath
)

install(TARGETS calculator_utility
        ARCHIVE DESTINATION /usr/local/lib/
        LIBRARY DESTINATION /usr/local/lib/
        RUNTIME DESTINATION /usr/local/bin/
)

#clang-format
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

#clang-tidy
find_program(CLANG_TIDY_EXE "clang-tidy")

if(CLANG_TIDY_EXE)
    message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
    set_target_properties(calculator_utility PROPERTIES 
        CXX_CLANG_TIDY
        "${CLANG_TIDY_EXE};-p=${CMAKE_BINARY_DIR}")
else()
    message(WARNING "clang-tidy not found!")
endif()