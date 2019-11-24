# test driver
add_executable(driver EXCLUDE_FROM_ALL main.cpp)

target_include_directories(driver
    PUBLIC
        ${PROJECT_SOURCE_DIR}/pbar
)
target_compile_features(driver
    PRIVATE
        cxx_std_11
)
set_target_properties(driver PROPERTIES
    CXX_EXTENSIONS OFF
)
target_compile_options(driver
    PRIVATE
        -Wall
        -Wextra
        -pedantic
        -O0
)

target_link_libraries(driver
    PUBLIC pbar
)