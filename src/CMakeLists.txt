# Modify the location of an executable output
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

# Target: rumraisin
add_executable(rumraisin
    main.cc
)
target_compile_features(rumraisin PUBLIC cxx_std_20)
