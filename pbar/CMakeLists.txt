add_library(progressbar SHARED)
target_sources(progressbar
    INTERFACE pbar.h
    PRIVATE   pbar.cpp
)
target_include_directories(progressbar
    PRIVATE ${CMAKE_SOURCE_DIR}
)
target_compile_features(progressbar
    PRIVATE
        cxx_std_11
)
set_target_properties(progressbar PROPERTIES
    CXX_EXTENSIONS OFF
)
target_compile_options(progressbar
    PRIVATE
        -Wall
        -Wextra
        -pedantic
        -Werror
        -O3
)
target_link_libraries(progressbar
    PRIVATE utils
)