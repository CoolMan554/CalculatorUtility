#pragma once

#include "CalculationRequest.h"

class Checker{
public:
    Checker() = default;
    ~Checker() = default;
    /**
     * @brief Validates parsed input data.
     *
     * @throws std::runtime_error if validation fails
     */
    void validate_input(const CalculationRequest& req) const;
};