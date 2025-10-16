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
    return x;  // <== REPLACE WITH PROVIDED IMPLEMENTATION
}

double applyNewtonStep(double x) {
    return x;  // <== REPLACE WITH PROVIDED IMPLEMENTATION
}

double computeInverseDerivative(double x) {
    return x;  // <== REPLACE WITH PROVIDED IMPLEMENTATION
}

double evaluate(double x, ModeSet modes) {


    double result = normalize(x);

    
    return result;
}

}
