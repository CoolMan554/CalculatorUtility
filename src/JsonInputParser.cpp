#include "JsonInputParser.h"
#include "Logger.h"
#include "nlohmann/json.hpp"

// for convenience
using json = nlohmann::json;

CalculationRequest JsonInputParser::parse(const std::string &str) {

    if (str.empty()) {
        throw std::runtime_error("Function JsonInputParser: There is no input data");
    }

    json input_json = json::parse(str);

    CalculationRequest req;

    if (!input_json.contains("arg1") && input_json["arg1"].empty()) {
        throw std::runtime_error("Function parse: The first argument is missing!");
    }

    req.first_argument = input_json.at("arg1").get<double>();

    if (!input_json.contains("operation") && input_json["operation"].empty() &&
        input_json["operation"].size() > 1) {
        throw std::runtime_error("Function parse: The operation is missing!");
    }

    std::string op_str = input_json.at("operation").get<std::string>();

    if (op_str.size() != 1) {
        throw std::runtime_error("Operation must be a single character");
    }

    req.operation = op_str[0];

    if (req.operation != '!' && !input_json.contains("arg2") && input_json["arg2"].empty()) {
        throw std::runtime_error("Function parse: The second argument is missing!");
    }

    if (req.operation != '!') {
        req.second_argument = input_json.at("arg2").get<double>();
    }

    Logger::instance().info("Parsing in JSON format was successful");

    return req;
}