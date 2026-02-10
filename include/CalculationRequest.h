#pragma once

#include <string>

struct CalculationRequest {
    double first_argument{0.0};
    double second_argument{0.0};
    std::string operation;
    bool show_help{false};
};