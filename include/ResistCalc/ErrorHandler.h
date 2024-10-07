/*
 * This header file declares the error handling functions for the ResistCalc
 * project. It includes functions for reporting errors and validating junction
 * indices in electrical circuit calculations.
 */

#ifndef ERROR_HANDLER_H_
#define ERROR_HANDLER_H_

#include <cstddef>
#include <string>

namespace resist_calc {

// Displays an error message with platform-specific formatting.
void
report_error(const std::string &message);

// Validates if junction indices 'u' and 'v' are within range.
bool
is_invalid_junction(std::size_t u, std::size_t v, std::size_t num_junctions);

} // namespace resist_calc

#endif // ERROR_HANDLER_H_
