#pragma once

#include <string>

struct CalculationRequest
{
    char operation;
    double first_argument{0.0};
    double second_argument{0.0};   
    double result{0.0};
};