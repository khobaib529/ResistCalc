/*
 * Circuit Class Implementation
 *
 * This file implements the Circuit class to calculate the total resistance of a
 * circuit represented as a directed graph.
 */

#include <ResistCalc/Circuit.h>

#include <cstddef>
#include <iostream>
#include <set>
#include <stdexcept>
#include <utility>
#include <vector>

namespace resist_calc {

// Constructor to initialize the circuit with a specified number of junctions.
Circuit::Circuit(std::size_t V) : edge_cnt(0), V(V) {
  adj_ls.resize(V);
  indegree.resize(V);
}

// Default constructor.
Circuit::Circuit() : edge_cnt(0), V(0) {}

// Sets the number of junctions in the circuit.
void
Circuit::set_junctions(std::size_t V) {
  if (int(V) < 0) {
    throw std::runtime_error(
        "Invalid number of junctions: The number of junctions cannot be "
        "negative.");
  }
  this->V = V;
  adj_ls.resize(V);
  indegree.resize(V);
}

// Checks if the given node has a series connection.
bool
Circuit::is_series_connection(std::size_t node) {
  return adj_ls[node].size() == 1 && indegree[node] == 1;
}

// Adjusts the resistance of parallel connections.
void
Circuit::adjust_parallel_connections(std::size_t node) {
  std::multiset<std::pair<std::size_t, double>>::iterator it =
      adj_ls[node].begin();

  while (it != adj_ls[node].end()) {
    std::multiset<std::pair<std::size_t, double>>::iterator start = it;
    std::multiset<std::pair<std::size_t, double>>::iterator end =
        ++std::multiset<std::pair<std::size_t, double>>::iterator(it);

    double reciprocal_sum = 0;
    bool flag = false;

    while (end != adj_ls[node].end() && it->first == end->first) {
      reciprocal_sum += (1.0 / end->second);
      end = adj_ls[node].erase(end);
      --indegree[it->first];
      --edge_cnt;
      flag = true;
    }

    if (flag == true) {
      reciprocal_sum += (1.0 / start->second);
      adj_ls[node].erase(start);
      adj_ls[node].insert(std::make_pair(start->first, 1.0 / reciprocal_sum));
    }

    it = end;
  }
}

// Performs a depth-first search on the circuit to adjust connections.
void
Circuit::dfs(std::size_t node) {
  std::size_t prev_edge_cnt = edge_cnt;
  for (const std::pair<std::size_t, double>& it : adj_ls[node]) {
    std::size_t adj_node = it.first;
    double resistance = it.second;
    // checking for resistence adjustment
    if (is_series_connection(adj_node)) {
      double new_resistence = resistance + adj_ls[adj_node].begin()->second;
      std::size_t node_to_connect = adj_ls[adj_node].begin()->first;

      adj_ls[adj_node].clear();
      --indegree[adj_node];
      --edge_cnt;

      adj_ls[node].erase(std::make_pair(adj_node, resistance));
      adj_ls[node].insert(std::make_pair(node_to_connect, new_resistence));
    } else {
      dfs(adj_node);
    }
  }
  adjust_parallel_connections(node);
  if (edge_cnt < prev_edge_cnt) {
    dfs(node);
  }
}

// Connects two junctions in the circuit.
void
Circuit::connect(std::size_t u, std::size_t v, double resistance) {
  if (u >= V || v >= V || resistance < 0) {
    throw std::runtime_error("Error: Invalid parameters for connect().");
  }
  ++edge_cnt;
  ++indegree[v];
  adj_ls[u].insert(std::make_pair(v, resistance));
}

// Calculates the total resistance of the circuit.
double
Circuit::calculate_total_resistance() {
  dfs(0);
  // Ensure there is exactly one connection left; otherwise, the circuit is
  // unsolvable.
  if (edge_cnt != 1) {
    throw std::runtime_error(
        "Error: Unable to solve the circuit. Check connectivity and "
        "junctions.");
  }
  return adj_ls[0].begin()->second;
}
} // namespace resist_calc