cmake_minimum_required(VERSION 3.15)

cmake_policy(SET CMP0069 NEW)
include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_support OUTPUT ipo_err_info LANGUAGES CXX)
if(ipo_support)
    message(STATUS "compiler supports interprocedural optimization")
else()
    message(WARNING "compiler does NOT support interprocedural optimization\nreason:\n${ipo_err_info}")
endif()

project(cpp_logger LANGUAGES CXX)

add_subdirectory(utils)
add_subdirectory(pbar)
add_subdirectory(examples)


#add_subdirectory(external)
#target_link_libraries(${PROJECT_NAME} ansi-escape::aesc)