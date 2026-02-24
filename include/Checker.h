#pragma once

#include "CalculationRequest.h"

class Checker {
  public:
    Checker() = default;
    ~Checker() = default;

    Checker(const Checker &) = default;
    Checker &operator=(const Checker &) = default;

    Checker(Checker &&) noexcept = default;
    Checker &operator=(Checker &&) noexcept = default;

    /**
     * @brief Validates parsed input data.
     *
     * @throws std::runtime_error if validation fails
     */
    void validate_input(const OperationKey &req) const;
};