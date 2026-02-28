#pragma once

#include <string>

struct CalculationRequest {
    char operation;
    double first_argument{0.0};
    double second_argument{0.0};
    double result{0.0};

    bool operator==(const CalculationRequest &key) const {
        return operation == key.operation && first_argument == key.first_argument &&
               second_argument == key.second_argument;
    }
};

struct CalculationKeyHash {
    std::size_t operator()(const CalculationRequest &key) const noexcept {
        std::size_t h1 = std::hash<char>{}(key.operation);
        std::size_t h2 = std::hash<double>{}(key.first_argument);
        std::size_t h3 = std::hash<double>{}(key.second_argument);

        return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h3 << 3);
    }
};