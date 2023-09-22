# Variable
set(PATH_TO_SRC ${PROJECT_SOURCE_DIR}/src)

# Target: vec_test
add_executable(vec_test
    vec_test.cc

    ${PATH_TO_SRC}/models/general.cc
)
target_compile_features(vec_test PUBLIC cxx_std_20)
target_include_directories(vec_test
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)
