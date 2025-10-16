#include "math.hpp"
#include <algorithm>

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
    const double y = (x + CFG.offset) * CFG.scale;
    return std::clamp(y,
        static_cast<double>(CFG.lo),
        static_cast<double>(CFG.hi));
}


double computeFunctionValue(double x) {
    return x;  // <== REPLACE WITH PROVIDED IMPLEMENTATION
}

double computeDefiniteIntegral(double x) {
    return Fantiderivative(x) - Fantiderivative(0.0);
}

double applyNewtonStep(double x) {
    double deriv = fprime(x);
    if (std::abs(deriv) >= EPS) {
        return x - f(x) / deriv;
    }
    return x; // Guard: if f'(x) ≈ 0, no refinement
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
    result = normalize(x);
    if (modes & NEWTON_STEP) {
        result = applyNewtonStep(result);
    }
    if (modes & DERIVATIVE) {
        result = computeInverseDerivative(result);
    }
    if (modes & INTEGRAL) {
        result = computeDefiniteIntegral(result);
    }
    return result;
}

}
