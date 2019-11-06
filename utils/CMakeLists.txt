add_library(utils INTERFACE)
target_include_directories(utils
    INTERFACE .
)
set_source_files_properties(color.hpp PROPERTIES
    LANGUAGE CXX
    HEADER_FILE_ONLY ON
)
target_compile_features(utils
    INTERFACE
        cxx_std_11
)
target_compile_options(utils
    INTERFACE
        -Wall
        -Wextra
        -pedantic
        -Werror
        #-O0
        #-g3
        -O3
)