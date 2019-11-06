cmake_minimum_required(VERSION 3.15)

cmake_policy(SET CMP0069 NEW)
cmake_policy(SET CMP0079 NEW)
include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_support OUTPUT ipo_out LANGUAGES CXX)

project(cpp_logger LANGUAGES CXX)

add_subdirectory(utils)
add_subdirectory(logger)
add_subdirectory(progressbar)
add_subdirectory(examples)


#add_subdirectory(external)
#target_link_libraries(${PROJECT_NAME} ansi-escape::aesc)