#pragma once

#include "CalculationRequest.h"

class Calculator {
  public:
    Calculator() = default;
    ~Calculator() = default;

    Calculator(const Calculator &) = default;
    Calculator &operator=(const Calculator &) = default;

    Calculator(Calculator &&) noexcept = default;
    Calculator &operator=(Calculator &&) noexcept = default;

    /**
     * @brief Performs calculation based on parsed input.
     */
    double calculate(const OperationKey &req) const;
};