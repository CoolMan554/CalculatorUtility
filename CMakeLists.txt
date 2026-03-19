cmake_minimum_required(VERSION 3.28)

include(FetchContent)

project(calculator_utility VERSION 1.0)

option(ENABLE_TSAN "Enable ThreadSanitizer" OFF)

if(ENABLE_TSAN)
    add_compile_options(
        -fsanitize=thread
        -fno-omit-frame-pointer        
        -g
        -O1
    )

    add_link_options(
        -fsanitize=thread        
    )
endif()

add_library(calculator_core
        src/Application.cpp
        src/Calculator.cpp
        src/Checker.cpp
        src/CliParser.cpp
        src/JsonInputParser.cpp
        src/Printer.cpp
        src/Logger.cpp
        src/PostgreSqlDB.cpp
        src/CacheManager.cpp
        src/DBConfig.cpp
)

target_include_directories(calculator_core 
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# C++ standard (add --std=c++17)
target_compile_features(calculator_core PUBLIC cxx_std_17)

set_target_properties(calculator_core PROPERTIES
    CXX_STANDARD_REQUIRED YES #lowering the standard NO
    CXX_EXTENSIONS NO #banning GNU-CLANG extensions
)

# LIBRARY

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
        GIT_TAG v1.17.0
)

FetchContent_MakeAvailable(
        spdlog
)

# # gRPC It's too long to wait

# FetchContent_Declare(
#     grpc
#     GIT_REPOSITORY https://github.com/grpc/grpc.git
#     GIT_TAG v1.78.1
# )

# set(FETCHCONTENT_QUIET OFF)
# FetchContent_MakeAvailable(grpc)

# Proto files
set(PROTO_DIR ${CMAKE_CURRENT_SOURCE_DIR}/proto)
set(PROTO_FILE ${PROTO_DIR}/calculator.proto)

# Generated files
set(GENERATED_DIR ${CMAKE_BINARY_DIR}/generated)
file(MAKE_DIRECTORY ${GENERATED_DIR})

set(PROTO_SRCS
    ${GENERATED_DIR}/calculator.pb.cc
)

set(PROTO_HDRS
    ${GENERATED_DIR}/calculator.pb.h
)

set(GRPC_SRCS
    ${GENERATED_DIR}/calculator.grpc.pb.cc
)

set(GRPC_HDRS
    ${GENERATED_DIR}/calculator.grpc.pb.h
)

add_custom_command(
    OUTPUT ${PROTO_SRCS} ${PROTO_HDRS} ${GRPC_SRCS} ${GRPC_HDRS}
    COMMAND protobuf::protoc
    ARGS --grpc_out ${GENERATED_DIR}
         --cpp_out ${GENERATED_DIR}
         -I ${PROTO_DIR}
         --plugin=protoc-gen-grpc=/usr/bin/grpc_cpp_plugin
         ${PROTO_FILE}
    DEPENDS ${PROTO_FILE}
)

add_library(grpc_proto
    ${PROTO_SRCS}
    ${GRPC_SRCS}
)

add_custom_target(generate_proto ALL
    DEPENDS ${PROTO_SRCS} ${GRPC_SRCS}
)

add_dependencies(grpc_proto generate_proto)

target_include_directories(grpc_proto PUBLIC 
    ${GENERATED_DIR} 
)

target_link_libraries(grpc_proto
    PUBLIC
    gRPC::grpc++
    gRPC::gpr
    protobuf::libprotobuf
)

add_library(grpc_client 
    src/grpc/GrpcClient.cpp
)

target_include_directories(grpc_client 
    PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(grpc_client 
    PUBLIC
    grpc_proto
)

# psql

find_package(PostgreSQL REQUIRED)

if (PostgreSQL_FOUND)
    include_directories(${PostgreSQL_INCLUDE_DIRS})
    target_link_libraries(calculator_core PRIVATE ${PostgreSQL_LIBRARIES})
else()
    message(FATAL_ERROR "PostgreSQL library not found")
endif()

target_link_libraries(calculator_core 
        PUBLIC
        library_math
        nlohmann_json::nlohmann_json
        spdlog::spdlog
        grpc_client
)

find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)

add_executable(calculator_server
    src/grpc/GrpcServer.cpp
)

target_link_libraries(calculator_server
    PRIVATE
    calculator_core
)

target_compile_options(calculator_server PRIVATE
    -Wall
    -Wextra
    -Wpedantic    
    -fno-omit-frame-pointer #perf
)

# Tests
enable_testing()
add_subdirectory(tests)

# install
install(TARGETS calculator_server
        ARCHIVE DESTINATION /usr/local/lib/
        LIBRARY DESTINATION /usr/local/lib/
        RUNTIME DESTINATION /usr/local/bin/
)

install(FILES config/config_db.json
        DESTINATION /etc/calculator_utility
)

install(FILES 
        ${CMAKE_SOURCE_DIR}/service/systemd/calculator_server.service
        DESTINATION /etc/systemd/system
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

configure_file(
    ${CMAKE_SOURCE_DIR}/config/config_db.json
    ${CMAKE_BINARY_DIR}/config/config_db.json
    COPYONLY
)

#port Server

set(GRPC_SERVER_PORT 50051 CACHE STRING "Port for gRPC server")

add_definitions(-DGRPC_SERVER_PORT=${GRPC_SERVER_PORT})
message(STATUS "gRPC Server will run on port: ${GRPC_SERVER_PORT}")