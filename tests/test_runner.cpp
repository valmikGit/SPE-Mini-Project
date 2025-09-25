#include <iostream>
#include <cmath>
#include <string>
#include "../src/calculator.hpp"

using namespace std;
using namespace calc;

int main() {
    int failed = 0;
    auto expect = [&](bool cond, const string &msg) {
        if (!cond) {
            cout << "FAIL: " << msg << "\n";
            ++failed;
        } else {
            cout << "OK: " << msg << "\n";
        }
    };

    // sqrt tests
    auto r1 = sqrt_op(4.0);
    expect(r1 && fabs(*r1 - 2.0) < 1e-9, "sqrt(4) == 2");

    auto r1b = sqrt_op(-1.0);
    expect(!r1b, "sqrt(-1) returns nullopt");

    // factorial tests
    auto f0 = factorial_op(0.0);
    expect(f0 && *f0 == 1ULL, "0! == 1");

    auto f5 = factorial_op(5.0);
    expect(f5 && *f5 == 120ULL, "5! == 120");

    auto fneg = factorial_op(-3.0);
    expect(!fneg, "-3! invalid");

    auto fnonint = factorial_op(4.5);
    expect(!fnonint, "4.5! invalid");

    auto flarge = factorial_op(21.0);
    expect(!flarge, "21! too large -> invalid (overflow guard)");

    // ln tests
    auto ln1 = ln_op(M_E);
    expect(ln1 && fabs(*ln1 - 1.0) < 1e-9, "ln(e) == 1");

    auto lnneg = ln_op(-1.0);
    expect(!lnneg, "ln(-1) invalid");

    // power tests
    auto p1 = power_op(2.0, 10.0);
    expect(p1 && fabs(*p1 - 1024.0) < 1e-6, "2^10 == 1024");

    auto p2 = power_op(-1.0, 0.5); // sqrt(-1) -> NaN
    expect(!p2, "(-1)^0.5 invalid -> nullopt");

    if (failed == 0) {
        cout << "ALL TESTS PASSED\n";
        return 0;
    } else {
        cout << failed << " tests failed\n";
        return 1;
    }
}