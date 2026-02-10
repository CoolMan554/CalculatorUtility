#pragma once

#include "CalculationRequest.h"

class JsonInputParser {
  public:
    JsonInputParser() = default;
    ~JsonInputParser() = default;

    CalculationRequest parse(const std::string &input_data);
};