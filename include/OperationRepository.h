#pragma once

#include "CalculationRequest.h"
#include <functional>

struct OperationKey {
    char operation;
    double first_argument{0.0};
    double second_argument{0.0};    

    bool operator==(const OperationKey& key) const{
        return operation == key.operation &&
               first_argument == key.first_argument &&
               second_argument == key.second_argument;
    }


    static OperationKey makeKey(const CalculationRequest& op)
    {
        return OperationKey{
            op.operation,
            op.first_argument,
            op.second_argument
        };
    }
};

struct OperationKeyHash {
    std::size_t operator()(const OperationKey& key) const noexcept {
        std::size_t h1 = std::hash<char>{}(key.operation);
        std::size_t h2 = std::hash<double>{}(key.first_argument);
        std::size_t h3 = std::hash<double>{}(key.second_argument);        

        return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h3 << 3);
    }
};