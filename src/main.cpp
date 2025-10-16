#include <iostream>
#include "math.hpp"

int main() {
    std::cout << "All modes = " << dm::evaluate(2.0, dm::VALUE | dm::INTEGRAL | dm::NEWTON_STEP | dm::DERIVATIVE) << "\n";
}
