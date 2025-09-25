#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <string>
#include <optional>

namespace calc {

// Compute square root. Returns std::nullopt on invalid input (negative).
std::optional<double> sqrt_op(double x);

// Compute factorial for non-negative integers n (n >= 0).
// Returns std::nullopt on invalid input (negative or non-integer or too large).
std::optional<unsigned long long> factorial_op(double x);

// Natural logarithm (ln). Returns std::nullopt on invalid input (<=0).
std::optional<double> ln_op(double x);

// Power function x^b
std::optional<double> power_op(double x, double b);

// Utility: check if double is integer within epsilon
bool is_integer(double x, double eps = 1e-9);

} // namespace calc

#endif // CALCULATOR_HPP