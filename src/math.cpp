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
    return x;  // <== REPLACE WITH PROVIDED IMPLEMENTATION
}

double computeDefiniteIntegral(double x) {
    return x;  // <== REPLACE WITH PROVIDED IMPLEMENTATION
}

double applyNewtonStep(double x) {
    return x;  // <== REPLACE WITH PROVIDED IMPLEMENTATION
}

double computeInverseDerivative(double x) {
    double deriv = fprime(x);
    if (std::abs(deriv) >= EPS) {
        return 1.0 / deriv;
    }
    return x;
}

double evaluate(double x, ModeSet modes) {
    double result = x;
    if (modes & DERIVATIVE) {
        result = computeInverseDerivative(result);
    }
    return result;
}

}
