#pragma once

#include "CalculationRequest.h"

class JsonInputParser {
  public:
    JsonInputParser() = default;
    ~JsonInputParser() = default;

    JsonInputParser(const JsonInputParser &) = default;
    JsonInputParser &operator=(const JsonInputParser &) = default;

    JsonInputParser(JsonInputParser &&) noexcept = default;
    JsonInputParser &operator=(JsonInputParser &&) noexcept = default;

    CalculationRequest parse(const std::string &input_data);
};