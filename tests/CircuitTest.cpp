/*
 * This file contains unit tests for the Circuit class using GoogleTest.
 * It verifies constructors, connections, resistance calculations, and edge
 * cases.
 */

#include <ResistCalc/Circuit.h>
#include <gtest/gtest.h>

#include <stdexcept>

class CircuitTest : public ::testing::Test {
 protected:
  resist_calc::Circuit circuit;

  void
  SetUp() override {}

  void
  TearDown() override {}
};

// 1. Test default constructor
TEST_F(CircuitTest, DefaultConstructor) {
  EXPECT_NO_THROW(resist_calc::Circuit circuit);
}

// 2. Test constructor with number of junctions
TEST_F(CircuitTest, ConstructorWithJunctions) {
  EXPECT_NO_THROW(circuit.set_junctions(3)); // Should not throw
}

// 3. Test setting junctions
TEST_F(CircuitTest, SetJunctions) {
  circuit.set_junctions(5);
  // Assuming get_junction_count() exists to retrieve the number of junctions
  EXPECT_THROW(circuit.connect(5, 0, 4), std::runtime_error);
}

// 4. Test connecting valid junctions
TEST_F(CircuitTest, ValidConnection) {
  circuit.set_junctions(3);
  EXPECT_NO_THROW(circuit.connect(0, 1, 50.0)); // Should not throw
  // Add validation for checking if the connection was made correctly
  EXPECT_DOUBLE_EQ(circuit.calculate_total_resistance(),
                   50.0); // Resistance of a single connection
}

// 5. Test connecting invalid junctions
TEST_F(CircuitTest, InvalidConnection) {
  circuit.set_junctions(2);
  EXPECT_THROW(circuit.connect(0, 3, 10.0),
               std::runtime_error); // Out of range junction
}

// 6. Test calculating total resistance for series resistors
TEST_F(CircuitTest, SeriesResistors) {
  circuit.set_junctions(3);
  circuit.connect(0, 1, 100.0);
  circuit.connect(1, 2, 50.0);
  EXPECT_DOUBLE_EQ(circuit.calculate_total_resistance(), 150.0);
}

// 7. Test calculating total resistance for parallel resistors
TEST_F(CircuitTest, ParallelResistors) {
  circuit.set_junctions(7);
  circuit.connect(0, 1, 0);
  circuit.connect(1, 2, 0);
  circuit.connect(1, 3, 0);
  circuit.connect(3, 5, 100);
  circuit.connect(2, 4, 100);
  circuit.connect(4, 6, 0);
  circuit.connect(5, 6, 0);
  // Assuming the method calculates total resistance correctly
  EXPECT_DOUBLE_EQ(circuit.calculate_total_resistance(),
                   50.0); // Parallel resistance
}

// 8. Test extremely high resistance
TEST_F(CircuitTest, ExtremelyHighResistance) {
  circuit.set_junctions(2);
  circuit.connect(0, 1, 1e9);
  EXPECT_DOUBLE_EQ(circuit.calculate_total_resistance(), 1e9);
}

// 9. Test handling negative resistance values
TEST_F(CircuitTest, NegativeResistance) {
  circuit.set_junctions(2);
  EXPECT_THROW(circuit.connect(0, 1, -50.0), std::runtime_error);
}

// 10. Test handling zero resistance (ideal wire)
TEST_F(CircuitTest, ZeroResistance) {
  circuit.set_junctions(2);
  circuit.connect(0, 1, 0.0);
  EXPECT_DOUBLE_EQ(circuit.calculate_total_resistance(), 0.0);
}

// 11. Test duplicate connections
TEST_F(CircuitTest, DuplicateConnections) {
  circuit.set_junctions(2);
  circuit.connect(0, 1, 100.0);
  circuit.connect(0, 1, 100.0);      // Duplicate connection
  double expected_resistance = 50.0; // Parallel of two 100 Ohm resistors
  EXPECT_DOUBLE_EQ(circuit.calculate_total_resistance(), expected_resistance);
}

// 12. Test empty circuit (no junctions)
TEST_F(CircuitTest, EmptyCircuit) {
  EXPECT_NO_THROW(circuit.set_junctions(0)); // Should not throw
}

// 13. Test invalid number of junctions
TEST_F(CircuitTest, InvalidNumberOfJunctions) {
  EXPECT_THROW(circuit.set_junctions(-1), std::runtime_error);
}

// 14. Test multiple connections between same junctions
TEST_F(CircuitTest, MultipleConnections) {
  circuit.set_junctions(2);
  circuit.connect(0, 1, 100.0);
  circuit.connect(0, 1, 200.0); // Parallel connection
  double expected_resistance = 1.0 / (1.0 / 100.0 + 1.0 / 200.0);
  EXPECT_DOUBLE_EQ(circuit.calculate_total_resistance(), expected_resistance);
}
