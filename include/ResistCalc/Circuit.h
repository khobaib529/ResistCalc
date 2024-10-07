/**
 * @file Circuit.h
 * @brief Header file for the Circuit class in the OhmAnalyzer project.
 *
 * This file contains the declaration of the Circuit class, which provides
 * methods for managing electrical circuits, calculating total resistance,
 * and handling connections between junctions.
 */

#ifndef RESIST_CALC_CIRCUIT_H_
#define RESIST_CALC_CIRCUIT_H_

#include <cstddef> // For std::size_t
#include <set>     // For std::multiset
#include <utility> // For std::pair
#include <vector>  // For std::vector

namespace resist_calc {
class Circuit {
 private:
  // Checks if a node needs resistance adjustment
  bool
  is_series_connection(std::size_t node);

  // Adjusts parallel connections for a given node
  void
  adjust_parallel_connections(std::size_t node);

  // Depth-first search traversal
  void
  dfs(std::size_t node);

 public:
  // Default constructor
  Circuit(); // Initializes with 0 junctions

  // Constructor to initialize the circuit with V junctions
  Circuit(std::size_t V);

  // Method to set the number of junctions
  void
  set_junctions(std::size_t V);

  // Connects junction u to junction v with a given resistance
  void
  connect(std::size_t u, std::size_t v, double resistance);

  // Calculates and returns the total resistance of the circuit
  double
  calculate_total_resistance();

 private:
  std::size_t edge_cnt;
  std::vector<std::size_t> indegree;
  std::size_t V; // Number of vertices in the graph
  std::vector<std::multiset<std::pair<std::size_t, double>>>
      adj_ls; // Adjacency list of the graph {junction, resistance}
};
} // namespace resist_calc

#endif // RESIST_CALC_CIRCUIT_H_