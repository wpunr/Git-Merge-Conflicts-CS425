#pragma once
#include <algorithm>
#include <cmath>

namespace dm {

struct Config {int scale; int offset; int lo; int hi;};
inline Config CFG{1, 0, -100, 100};

enum Mode {
    NONE = 0,
    VALUE = 1 << 0,
    INTEGRAL = 1 << 1,
    NEWTON_STEP = 1 << 2,
    DERIVATIVE = 1 << 3
};

using ModeSet = int;

static constexpr double EPS = 1e-9;
static constexpr double DELTA = 1e-3;

double f(double x);
double fprime(double x);
double Fantiderivative(double x);

double computeFunctionValue(double x);
double computeDefiniteIntegral(double x);
double applyNewtonStep(double x);
double computeInverseDerivative(double x);

double normalize(double x);
double evaluate(double x, ModeSet modes = Mode::VALUE);
}
