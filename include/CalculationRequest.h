#pragma once

#include <string>

struct CalculationRequest {
    double first_argument{0.0};
    double second_argument{0.0};
    char operation;
    bool show_help{false};
    double result{0.0};
};