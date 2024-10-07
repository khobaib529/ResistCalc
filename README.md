# ResistCalc

## Description

**ResistCalc** is a C++ software application designed to calculate the total resistance of a given electrical circuit. The circuit is represented as a directed graph, where the direction of the edges indicates the flow of electricity.

## Build Guide

### Requirements
- C++14 or later
- CMake 3.14 or higher
- A compatible C++ compiler (e.g., GCC, Clang, or MSVC)
- GoogleTest (for running unit tests)

### Building the Project (Without Tests)

1. **Clone the repository**:
    ```bash
    git clone https://github.com/khobaib529/ResistCalc.git
    cd ResistCalc
    ```

2. **Create a build directory**:
    ```bash
    mkdir build
    cd build
    ```

3. **Generate the build files using CMake**:
    ```bash
    cmake ../
    ```

4. **Build the project**:
    ```bash
    cmake --build .
    ```

This will generate the executable in the `build` directory. You can run the program by executing:
```bash
./ResistCalc
```

### Building the Project (With Tests)

1. **Follow steps 1-2** from the previous section.

2. **Enable tests during the CMake configuration**:
    ```bash
    cmake -DBUILD_TESTS=ON ../
    ```

3. **Build the project along with tests**:
    ```bash
    cmake --build .
    ```

4. **Run the tests**:
    After the build is complete, you can run all tests using:
    ```bash
    ctest --verbose
    ```


