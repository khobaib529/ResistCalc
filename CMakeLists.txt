# ----------------------------------------------------------------------------
#  Root CMake file for ResistCalc
#
#    From the off-tree build directory, invoke:
#      $ cmake <PATH_TO_RESIST_CALC_ROOT>
#
# ----------------------------------------------------------------------------
# Disable in-source builds to prevent source tree corruption.

if(" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
  message(FATAL_ERROR "
FATAL: In-source builds are not allowed.
       You should create a separate directory for build files.
")
endif()

cmake_minimum_required(VERSION 3.14)

# Define the project name and version
project(
    ResistCalc 
    VERSION 1.0.0
    LANGUAGES CXX
)

# Set the C++ standard to be used for the project
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Create a static library for the core functionalities of OhmAnalyzer
# The source files for the core library are specified here
add_library(
    ResistCalcCore
    src/Circuit.cpp
    src/ResistCalc.cpp
    src/ErrorHandler.cpp
    )
target_include_directories(ResistCalcCore PUBLIC include)

# Create the main executable target for the project
add_executable(ResistCalc src/main.cpp)
target_link_libraries(ResistCalc PRIVATE ResistCalcCore)

# Add any necessary compiler flags based on the platform
if(WIN32)
    # Windows specific flags
    message(STATUS "Configuring for Windows")
elseif(APPLE)
    # macOS specific flags
    message(STATUS "Configuring for macOS")
elseif(UNIX)
    # Linux specific flags
    message(STATUS "Configuring for Linux")
endif()

# If BUILD_TESTS is defined, add the tests subdirectory
if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests) # Add test files
endif(BUILD_TESTS)