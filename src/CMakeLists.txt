# Modify the location of an executable output
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

# Target: rumraisin
add_executable(rumraisin
    main.cc

    controllers/loop.cc

    interfaces/config.cc
    interfaces/general.cc
    interfaces/graphics.cc
    interfaces/keyboard.cc
    interfaces/timer.cc
    interfaces/winfunc.cc

    models/entity.cc
    models/general.cc
)
target_compile_features(rumraisin PUBLIC cxx_std_20)
target_include_directories(rumraisin
    PUBLIC
        ${PATH_TO_SDL2}/include
        ${PROJECT_SOURCE_DIR}/include
)
target_link_directories(rumraisin PUBLIC ${PATH_TO_SDL2}/lib)
target_link_libraries(rumraisin PUBLIC ${SDL2_LIBRARIES})
