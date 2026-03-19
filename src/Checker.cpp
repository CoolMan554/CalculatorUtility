#include "Checker.h"
#include "Logger.h"

bool Checker::validate_input(const CalculationRequest &req) const {
    // На ноль делить нельзя
    if (req.operation == '/' && req.second_argument == 0.0) {
        return false;
    }

    Logger::instance().info("Verification of the input data was successful");

    return true;
}