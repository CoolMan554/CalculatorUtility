cmake_minimum_required(VERSION 3.5)

project(calculator_utility)

add_subdirectory(lib)

add_executable(calculator_utility
        main.cpp            
)

target_link_libraries(calculator_utility
        PRIVATE
        math
)

target_include_directories(calculator_utility
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/lib
)

install(TARGETS calculator_utility
        ARCHIVE DESTINATION /usr/local/lib/
        LIBRARY DESTINATION /usr/local/lib/
        RUNTIME DESTINATION /usr/local/bin/
)