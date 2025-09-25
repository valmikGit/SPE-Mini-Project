#include "calculator.hpp"
#include <cmath>
#include <limits>
#include <stdexcept>

namespace calc {

bool is_integer(double x, double eps) {
    double r = std::round(x);
    return std::fabs(x - r) <= eps;
}

std::optional<double> sqrt_op(double x) {
    if (x < 0.0) return std::nullopt;
    return std::sqrt(x);
}

std::optional<unsigned long long> factorial_op(double x) {
    // Factorial only defined for non-negative integers here.
    if (x < 0.0) return std::nullopt;
    if (!is_integer(x)) return std::nullopt;
    long long n = static_cast<long long>(std::llround(x));
    // limit to avoid overflow; 20! fits in unsigned long long? 20! = 2.43e18 fits, 21! overflows.
    if (n > 20) return std::nullopt;
    unsigned long long res = 1ULL;
    for (long long i = 2; i <= n; ++i) res *= static_cast<unsigned long long>(i);
    return res;
}

std::optional<double> ln_op(double x) {
    if (x <= 0.0) return std::nullopt;
    return std::log(x);
}

std::optional<double> power_op(double x, double b) {
    // For now we forward to pow. Some edge cases (negative base with non-integer exponent) produce NaN.
    double r = std::pow(x, b);
    if (std::isnan(r) || std::isinf(r)) return std::nullopt;
    return r;
}

} // namespace calc