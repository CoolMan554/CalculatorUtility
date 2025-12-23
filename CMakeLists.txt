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

#clang-format
find_program(CLANG_FORMAT_EXE  clang-format)
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