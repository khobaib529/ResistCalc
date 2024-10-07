/*
 * This file provides functions for error reporting and validation of
 * junction indices in the ResistCalc project. It handles platform-specific
 * error message formatting (e.g., colored output for different terminals).
 */

#include <ResistCalc/ErrorHandler.h>

#include <cstddef>
#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

namespace resist_calc {

// Function to report errors with color-coding based on the platform
void
report_error(const std::string &message) {
#ifdef _WIN32
  HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(h_console, FOREGROUND_RED);
  std::cerr << "Error: ";
  SetConsoleTextAttribute(h_console,
                          FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
#else
  std::cerr << "\033[1;31m"
            << "Error: "
            << "\033[0m"; // ANSI color codes for red text
#endif
  std::cerr << message << std::endl;
}

// Function to check for invalid junction indices
bool
is_invalid_junction(std::size_t u, std::size_t v, std::size_t num_junctions) {
  if (u >= num_junctions) {
    report_error("Junction index 'u' (" + std::to_string(int(u)) +
                 ") is out of range. Valid range is [0, " +
                 std::to_string(num_junctions - 1) + "].");
    return 1;
  }
  if (v >= num_junctions) {
    report_error("Junction index 'v' (" + std::to_string(int(v)) +
                 ") is out of range. Valid range is [0, " +
                 std::to_string(num_junctions - 1) + "].");
    return 1;
  }
  return 0;
}

} // namespace resist_calc
