add_library(logger SHARED)
target_sources(logger
    INTERFACE Logger.h
    PRIVATE   Logger.cpp
)
target_include_directories(logger
    PRIVATE ${CMAKE_SOURCE_DIR}
)
target_compile_features(logger
    PRIVATE
        cxx_std_11
)
set_target_properties(logger PROPERTIES
    CXX_EXTENSIONS OFF
)
target_compile_options(logger
    PRIVATE
        -Wall
        -Wextra
        -pedantic
        -Werror
        #-O0
        #-g3
        -O3
)
target_link_libraries(logger
    PRIVATE utils
)