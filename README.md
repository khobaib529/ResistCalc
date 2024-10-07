# ResistCalc

## Description

**ResistCalc** is a C++ software application designed to calculate the total resistance of a given electrical circuit. The circuit is represented as a directed graph, where the direction of the edges indicates the flow of electricity.

## Usage Guide

**ResistCalc** is a command-line application that calculates the total resistance of an electrical circuit represented as a directed graph.

### How to Use

1. **Build the Project**: Follow the **Build Guide** to compile the project.
2. **Run the Application**: Execute the program from the `build` directory using the command line.

   To run the application with an input file, use the following command:

   ```bash
   cd build
   ./ResistCalc path/to/your/<input_file>

### Input File Format

The input file should contain:

1. **The first line**: An integer \( n \), which represents the number of junctions.
2. **Subsequent lines**: Each line should specify a connection in the following format:

### Subsequent Line Format

Each subsequent line after the first should define a connection between junctions in the following format:

- \( u \): Starting junction (0-indexed).
- \( v \): Ending junction (0-indexed).
- \( r \): Resistance value (in ohms).

### Example Input File (`input.txt`)

```bash
9
0 1 2
1 2 6
2 3 2
3 4 10
3 7 20
3 8 20
4 5 10
4 6 20
4 7 20
5 6 10
6 7 10
7 8 10
```

### Explanation of Input

- **9**: Indicates that there are 9 junctions (0 through 8).
- Each subsequent line describes a connection between two junctions with a specified resistance value, where the direction indicates that electricity flows from junction \( u \) to junction \( v \). For example:
  - `0 1 2`: There is a connection from junction 0 to junction 1 with a resistance of 2 ohms.
  - `3 4 10`: There is a connection from junction 3 to junction 4 with a resistance of 10 ohms.


### Circuit Representation

The `input.txt` file represents the graph used in my article:

[Solving Electrical Circuits: A Graph-Based Algorithm for Resistance Calculations](https://medium.com/@khobaib529/solving-electrical-circuits-a-graph-based-algorithm-for-resistance-calculations-921575c59946)

In this article, I provide a comprehensive visual solution to the circuit described in the input file, analyzing its behavior and resistance calculations based on the graph structure.

If you have created your `input.txt` file in your working directory, you can run the application using the following command:

```bash
./ResistCalc input.txt
```

This command will output the total resistance of the circuit described in the graph represented by the input file.

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


