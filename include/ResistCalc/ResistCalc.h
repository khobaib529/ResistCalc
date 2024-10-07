/*
 * This header file declares the main functions for the ResistCalc project.
 * It includes the function for loading a circuit from a file and the program's
 * entry point.
 */

#ifndef RESIST_CALC_H_
#define RESIST_CALC_H_

#include <ResistCalc/Circuit.h>

#include <string>

namespace resist_calc {

// Loads circuit data from a file and populates the Circuit object.
bool
load_circuit_from_file(const std::string& file_path, Circuit& circuit);

// Main entry point for the ResistCalc program.
int
ResistCalcMain(int argc, char* argv[]);
} // namespace resist_calc

#endif // RESIST_CALC_H_