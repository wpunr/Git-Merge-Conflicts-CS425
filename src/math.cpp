#include "math.hpp"

namespace dm {

double f(double x) { 
    return x*x*x - 3.0*x; 
}

double fprime(double x) { 
    return 3.0*x*x - 3.0; 
}

double Fantiderivative(double x) { 
    return 0.25*x*x*x*x - 1.5*x*x; 
}

double normalize(double x) {
    return x;
}


double computeFunctionValue(double x) {
    // Check if near critical points where f'(x) = 0 (x = ±1)
    if (std::abs(x - 1.0) < DELTA || std::abs(x + 1.0) < DELTA) {
        // Use linearization for stability
        double a = (std::abs(x - 1.0) < DELTA) ? 1.0 : -1.0;
        return f(a) + fprime(a) * (x - a);
    }
    return f(x);
}

double computeDefiniteIntegral(double x) {
    return x;  // <== REPLACE WITH PROVIDED IMPLEMENTATION
}

double applyNewtonStep(double x) {
    return x;  // <== REPLACE WITH PROVIDED IMPLEMENTATION
}

double computeInverseDerivative(double x) {
    return x;  // <== REPLACE WITH PROVIDED IMPLEMENTATION
}

double evaluate(double x, ModeSet modes) {
    double result = x;
    if (modes & VALUE) {
        result = computeFunctionValue(result);
    }
    return result;
}

}
