cmake_minimum_required(VERSION 3.26)
project(rumraisin CXX)

# Variables
set(PATH_TO_SDL2
    CACHE STRING
        "Path to a directory that contains SDL2 libraries."
)

set(SDL2_LIBRARIES)
if(WIN32)
    list(APPEND SDL2_LIBRARIES
        mingw32
        SDL2main
        SDL2
    )
endif()

add_subdirectory(src)
add_subdirectory(tests)
