#pragma once

#include "CalculationRequest.h"

class Calculator{
public:
    Calculator() = default;
    ~Calculator() = default;
    /**
     * @brief Performs calculation based on parsed input.
     */
    double calculate(const CalculationRequest& req) const;
};