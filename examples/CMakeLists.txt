# test driver
add_executable(driver EXCLUDE_FROM_ALL
    main.cpp
)
target_include_directories(driver
    PRIVATE ${CMAKE_SOURCE_DIR}
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
        #-O0
        #-g3
        -O3
)
target_link_libraries(driver
    PUBLIC utils logger progressbar
)