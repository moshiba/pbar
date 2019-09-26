cmake_minimum_required(VERSION 3.2)

project(cpp_logger)

add_compile_options(-std=c++14)
#add_compile_options(-O0 -g3)
add_compile_options(-O3)
# lots of warnings and all warnings as errors
add_compile_options(-Wall -Wextra -pedantic -Werror)

include_directories(
        include
)

aux_source_directory(src DIR_SRCS)

set(
        LIB
        ${DIR_SRCS}
)

add_executable(${PROJECT_NAME} main.cpp ${LIB})
