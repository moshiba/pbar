add_library(progressbar SHARED)
target_sources(progressbar
    INTERFACE pbar.h
    PRIVATE   pbar.cpp
)
target_include_directories(progressbar
    PUBLIC ${PROJECT_SOURCE_DIR}
    PRIVATE /usr/local/include
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
        #-Werror
        -Os
)
find_library(FIND_AESC aesc)
message(WARNING "path: ${FIND_AESC}")
target_link_libraries(progressbar PRIVATE ${FIND_AESC})
