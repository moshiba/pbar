if(${CMAKE_VERSION} VERSION_GREATER "3.9")
    cmake_minimum_required(VERSION 3.9)
    message(WARNING "Using CMake version 3.9")

    include(CheckIPOSupported)
    check_ipo_supported(RESULT ipo_support OUTPUT ipo_err_info LANGUAGES CXX)
    if(ipo_support)
        message(STATUS "compiler supports interprocedural optimization")
    else()
        message(WARNING "compiler does NOT support interprocedural optimization\nreason:\n${ipo_err_info}")
    endif()
else()
    cmake_minimum_required(VERSION 3.5)
    message(WARNING "CMake version less than 3.9, using version 3.5")
endif()

project(pbar LANGUAGES CXX)

include(GNUInstallDirs)
add_subdirectory(pbar)
add_subdirectory(examples EXCLUDE_FROM_ALL)

