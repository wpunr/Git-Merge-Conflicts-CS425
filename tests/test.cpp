#include "../src/math.hpp"
#include <iostream>
#include <cmath>

int passed = 0;
int failed = 0;

void test(bool condition, const char* testName) {
    if (condition) {
        std::cout << "PASS: " << testName << std::endl;
        passed++;
    } else {
        std::cout << "FAIL: " << testName << std::endl;
        failed++;
    }
}

void test_f() {
    std::cout << "\nTesting f():" << std::endl;
    test(dm::f(0.0) == 0.0, "f(0)");
    test(dm::f(1.0) == -2.0, "f(1)");
    test(dm::f(2.0) == 2.0, "f(2)");
}

void test_fprime() {
    std::cout << "\nTesting fprime():" << std::endl;
    test(dm::fprime(0.0) == -3.0, "fprime(0)");
    test(dm::fprime(1.0) == 0.0, "fprime(1)");
    test(dm::fprime(2.0) == 9.0, "fprime(2)");
}

void test_Fantiderivative() {
    std::cout << "\nTesting Fantiderivative():" << std::endl;
    test(dm::Fantiderivative(0.0) == 0.0, "Fantiderivative(0)");
    test(dm::Fantiderivative(1.0) == -1.25, "Fantiderivative(1)");
    test(dm::Fantiderivative(2.0) == -2.0, "Fantiderivative(2)");
}

void test_normalize() {
    std::cout << "\nTesting normalize():" << std::endl;
    dm::CFG = {1, 0, -100, 100};
    test(dm::normalize(0.0) == 0.0, "normalize(0)");
    test(dm::normalize(50.0) == 50.0, "normalize(50)");
    test(dm::normalize(150.0) == 100.0, "normalize(150) - clamps to max");
}

void test_computeFunctionValue() {
    std::cout << "\nTesting computeFunctionValue():" << std::endl;
    test(dm::computeFunctionValue(0.0) == 0.0, "computeFunctionValue(0) = 0");
    test(dm::computeFunctionValue(2.0) == 2.0, "computeFunctionValue(2) = 2");
    test(dm::computeFunctionValue(3.0) == 18.0, "computeFunctionValue(3) = 18");
    
    test(dm::computeFunctionValue(-2.0) == -2.0, "computeFunctionValue(-2) = -2");
}

void test_computeDefiniteIntegral() {
    std::cout << "\nTesting computeDefiniteIntegral():" << std::endl;

    test(dm::computeDefiniteIntegral(0.0) == 0.0, "∫[0,0] = 0");
    test(dm::computeDefiniteIntegral(2.0) == -2.0, "∫[0,2] = -2");
    test(dm::computeDefiniteIntegral(4.0) == 40.0, "∫[0,4] = 40");
    test(dm::computeDefiniteIntegral(-2.0) == -2.0, "∫[0,-2] = -2");
}

void test_applyNewtonStep() {
    std::cout << "\nTesting applyNewtonStep():" << std::endl;

    double x = 2.0;
    double expected = x - dm::f(x) / dm::fprime(x);
    test(dm::applyNewtonStep(x) == expected, "applyNewtonStep(2) = 2 - f(2)/f'(2)");
    
    x = 3.0;
    expected = x - dm::f(x) / dm::fprime(x);
    test(dm::applyNewtonStep(x) == expected, "applyNewtonStep(3) = 3 - f(3)/f'(3)");
    
    x = 1.0;
    test(dm::applyNewtonStep(x) == x, "applyNewtonStep(1) = 1 (f'(1)=0, guard active)");
}

void test_computeInverseDerivative() {
    std::cout << "\nTesting computeInverseDerivative():" << std::endl;

    test(dm::computeInverseDerivative(2.0) == 1.0/9.0, "1/f'(2) = 1/9");
    
    test(dm::computeInverseDerivative(3.0) == 1.0/24.0, "1/f'(3) = 1/24");
    
    test(dm::computeInverseDerivative(0.0) == -1.0/3.0, "1/f'(0) = -1/3");
    
    test(dm::computeInverseDerivative(1.0) == 1.0, "1/f'(1) = 1 (guard: f'(1)=0)");
}

void test_evaluate() {
    std::cout << "\nTesting evaluate():" << std::endl;
    dm::CFG = {1, 0, -100, 100};
    
    double x = 2.0;
    
    double expected_value = dm::computeFunctionValue(x);
    test(dm::evaluate(x, dm::VALUE) == expected_value, "VALUE: f(2) = 2");
    
    double expected_integral = dm::computeDefiniteIntegral(x);
    test(dm::evaluate(x, dm::INTEGRAL) == expected_integral, "INTEGRAL: ∫[0,2] f(t)dt = -2");
    
    double expected_newton = dm::applyNewtonStep(x);
    test(dm::evaluate(x, dm::NEWTON_STEP) == expected_newton, "NEWTON_STEP: Newton(2)");
    
    double expected_deriv = dm::computeInverseDerivative(x);
    test(dm::evaluate(x, dm::DERIVATIVE) == expected_deriv, "DERIVATIVE: 1/f'(2) = 1/9");
}

void test_main_argument() {
    std::cout << "\nTesting main.cpp argument:" << std::endl;
    dm::CFG = {1, 0, -100, 100};
    
    double expected = dm::computeFunctionValue(2.0);
    test(dm::evaluate(2.0, dm::VALUE) == expected, "evaluate(2.0, VALUE) = f(2) = 2");
}

void test_order() {
    std::cout << "\nOrder Enforcement:" << std::endl;
    dm::CFG = {1, 0, -100, 100};
    
    double x = 2.0;
    
    double step1_value = dm::computeFunctionValue(x);
    double expected_value_integral = dm::computeDefiniteIntegral(step1_value);
    test(dm::evaluate(x, dm::VALUE | dm::INTEGRAL) == expected_value_integral, 
         "ORDER TEST: ∫[0 to f(2)] = -2");
    
    double step1_integral = dm::computeDefiniteIntegral(x);
    double expected_integral_newton = dm::applyNewtonStep(step1_integral);
    test(dm::evaluate(x, dm::INTEGRAL | dm::NEWTON_STEP) == expected_integral_newton,
         "ORDER TEST: Newton(∫[0,2])");
    
    double stage2 = dm::computeDefiniteIntegral(dm::computeFunctionValue(x));
    double expected_vin = dm::applyNewtonStep(stage2);
    test(dm::evaluate(x, dm::VALUE | dm::INTEGRAL | dm::NEWTON_STEP) == expected_vin,
         "ORDER TEST: Newton(∫[0 to f(2)])");
    
    double stage1 = dm::computeFunctionValue(x);
    double stage2_full = dm::computeDefiniteIntegral(stage1);
    double stage3 = dm::applyNewtonStep(stage2_full);
    double expected_full = dm::computeInverseDerivative(stage3);
    test(dm::evaluate(x, dm::VALUE | dm::INTEGRAL | dm::NEWTON_STEP | dm::DERIVATIVE) == expected_full,
         "ORDER TEST: (1/f')(Newton(∫[0 to f(2)]))");
    
}

int main() {
    std::cout << "Running tests...\n" << std::endl;
    
    // Test basic functions
    test_f();
    test_fprime();
    test_Fantiderivative();
    test_normalize();
    
    // Test Student functions
    test_computeFunctionValue();
    test_computeDefiniteIntegral();
    test_applyNewtonStep();
    test_computeInverseDerivative();
    
    // Test outputs
    test_evaluate();
    test_main_argument();
    test_order();
    
    std::cout << "\n========================================" << std::endl;
    std::cout << "Results: " << passed << " passed, " << failed << " failed" << std::endl;
    std::cout << "========================================" << std::endl;
    
    return (failed == 0) ? 0 : 1;
}
