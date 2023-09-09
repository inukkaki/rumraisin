# rumraisin

Working in progress for now.

## How to build this

This project uses CMake to make a buildsystem.

The directory structure is as follows:
-   `./build` - A build directory. This is to be created by running the CMake
    commands mentioned later.
-   `./src` - A source directory.

First of all, generate a buildsystem by specifying both the source and build
directories:
```
cmake -G Ninja -S . -B build -DCMAKE_CXX_COMPILER=g++
```

To make an executable, run the following command:
```
cmake --build build --clean-first
```

The executable is in the project directory.
