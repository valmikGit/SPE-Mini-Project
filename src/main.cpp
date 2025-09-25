#include <iostream>
#include <limits>
#include <string>
#include "calculator.hpp"

using namespace std;
using namespace calc;

void print_menu() {
    cout << "Scientific Calculator\n";
    cout << "1) Square root (sqrt)\n";
    cout << "2) Factorial (!n)\n";
    cout << "3) Natural log (ln)\n";
    cout << "4) Power (x^b)\n";
    cout << "5) Exit\n";
    cout << "Choose option: ";
}

double read_double(const string &prompt) {
    double v;
    while (true) {
        cout << prompt;
        if (cin >> v) return v;
        cout << "Invalid number. Try again.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main() {
    while (true) {
        print_menu();
        int opt;
        if (!(cin >> opt)) {
            cout << "Invalid selection. Exiting.\n";
            break;
        }
        if (opt == 5) {
            cout << "Goodbye!\n";
            break;
        }
        switch (opt) {
            case 1: {
                double x = read_double("Enter x for sqrt(x): ");
                auto r = sqrt_op(x);
                if (!r) cout << "Error: square root undefined for negative values.\n";
                else cout << "sqrt(" << x << ") = " << *r << "\n";
                break;
            }
            case 2: {
                double n = read_double("Enter n for n! (non-negative integer): ");
                auto r = factorial_op(n);
                if (!r) cout << "Error: factorial defined for non-negative integers up to 20.\n";
                else cout << n << "! = " << *r << "\n";
                break;
            }
            case 3: {
                double x = read_double("Enter x for ln(x): ");
                auto r = ln_op(x);
                if (!r) cout << "Error: ln defined only for x > 0.\n";
                else cout << "ln(" << x << ") = " << *r << "\n";
                break;
            }
            case 4: {
                double x = read_double("Enter base x: ");
                double b = read_double("Enter exponent b: ");
                auto r = power_op(x,b);
                if (!r) cout << "Error: power undefined for given inputs (NaN/Inf).\n";
                else cout << x << "^" << b << " = " << *r << "\n";
                break;
            }
            default:
                cout << "Invalid choice.\n";
        }
        cout << "\n";
    }
    return 0;
}