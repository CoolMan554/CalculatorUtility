#include "Checker.h"
#include "Logger.h"

void Checker::validate_input(const CalculationRequest& req) const{

    if (req.operation.empty())
        throw std::runtime_error("Function validate_input: Operation is empty");

    // На ноль делить нельзя
    if (req.operation == "/" && req.second_argument == 0.0) {
        throw std::runtime_error("Function validate_input: You can't divided by zero!");
    }

    Logger::instance().info("Verification of the input data was successful");
}