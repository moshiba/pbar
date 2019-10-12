cmake_minimum_required(VERSION 3.5)

cmake_policy(SET CMP0069 NEW)
include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_support OUTPUT ipo_out LANGUAGES CXX)

project(cpp_logger LANGUAGES CXX)

add_library(${PROJECT_NAME} SHARED include/Logger.h)
target_compile_features(${PROJECT_NAME}
    PRIVATE
        cxx_std_11
)
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_EXTENSIONS OFF
)
target_compile_options(${PROJECT_NAME}
    PRIVATE
        -Wall
        -Wextra
        -pedantic
        -Werror
        #-O0
        #-g3
        -O3
)
target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)
add_subdirectory(src)


# test driver
add_executable(driver main.cpp)
target_compile_features(driver
    PRIVATE
        cxx_std_11
)
target_compile_options(driver
    PRIVATE
        #-O0
        #-g3
        -O3
)
target_link_libraries(driver PRIVATE ${PROJECT_NAME})

add_subdirectory(external)