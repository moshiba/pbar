add_library(pbar SHARED)
target_sources(pbar
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/pbar.hpp
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/pbar.cpp
)
target_include_directories(pbar
    PUBLIC
        ${PROJECT_SOURCE_DIR}
)
target_include_directories(pbar SYSTEM
# HACK: to find lib aesc
    PRIVATE
        /usr/include
        /usr/local/include
)
target_compile_features(pbar
    PRIVATE
        cxx_std_11
)
set_target_properties(pbar PROPERTIES
    CXX_EXTENSIONS OFF
)
target_compile_options(pbar
    PRIVATE
        -Wall
        -Wextra
        -pedantic
        #-Werror
        -Os
)
find_library(FIND_AESC aesc)
message(STATUS "\"aesc\" library path: ${FIND_AESC}")
target_link_libraries(pbar PRIVATE ${FIND_AESC})

install(
    TARGETS pbar
    DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(
    FILES pbar.hpp
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
