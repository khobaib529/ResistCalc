/*
 * This file contains the main entry point for the ResistCalc project. It loads
 * a circuit from a file, calculates the total resistance, and handles errors
 * during the process.
 */

#include <ResistCalc/Circuit.h>
#include <ResistCalc/ErrorHandler.h>

#include <cstdlib>
#include <fstream>
#include <iostream>

namespace resist_calc {

// Loads circuit data from a file and populates the Circuit object.
bool
load_circuit_from_file(const std::string &file_path, Circuit &circuit) {
  std::ifstream in_file(file_path);
  if (!in_file) {
    report_error("Unable to load circuit from file " + file_path);
    return 1;
  }

  std::size_t num_junctions;
  in_file >> num_junctions;

  circuit.set_junctions(num_junctions);

  std::size_t u, v;
  double resistance;
  while (in_file >> u >> v >> resistance) {
    if (is_invalid_junction(u, v, num_junctions)) {
      return 1;
    }
    circuit.connect(u, v, resistance);
  }
  in_file.close();
  return 0;
}

// Main entry point for the ResistCalc program.
int
ResistCalcMain(int argc, char *argv[]) {
  // Check if the correct number of arguments is provided
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <path_to_file>" << std::endl;
    return 1;
  }

  std::string file_path = argv[1];

  Circuit circuit;

  // Load the circuit from the specified file
  bool status = load_circuit_from_file(file_path, circuit);
  if (status != EXIT_SUCCESS) {
    return EXIT_FAILURE;
  }
  try {
    double total_resistance = circuit.calculate_total_resistance();
    std::cout << "Total Resistance: " << total_resistance << std::endl;
  } catch (const std::runtime_error &e) {
    report_error(e.what());
  } catch (...) {
    report_error("Unknown error");
  }

  return EXIT_SUCCESS;
}

} // namespace resist_calc
