cmake_minimum_required(VERSION 3.2)

project(cpp_logger)

add_definitions(-std=c++11)

include_directories(
        include
)

aux_source_directory(src DIR_SRCS)

set(
        LIB
        ${DIR_SRCS}
)

add_executable(${PROJECT_NAME} main.cpp ${LIB})