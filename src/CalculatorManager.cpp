#include <fstream>

#include "CalculatorManager.h"
#include "Logger.h"
#include "library_math.h"

void CalculatorManager::run(int argc, char **argv) {
    parse_arguments(argc, argv);

    if (!help_check_) {

        validate_input();

        calculate();

        print_result();
    }
}

void CalculatorManager::parse_arguments(int argc, char **argv) {
    // Resetting the counter
    optind = 1;
    opterr = 1;

    int opt;

    while ((opt = getopt_long(argc, argv, "hi:", long_opts.data(), nullptr)) != -1) {
        switch (opt) {
        case 'h':
            print_help(argv[0]);
            help_check_ = true;
            break;
        case 'i':
            if (optarg != nullptr) {
                std::string json_str = optarg;
                input_json_ = json::parse(json_str);
            }
            break;
        case '?':
            throw std::runtime_error("Function parser: The argument value is missing!");
            break;
        default:
            throw std::runtime_error("Function parser: There is no such operation!");
        }
    }

    Logger::instance().info("Parsing in JSON format was successful");
}

void CalculatorManager::validate_input() {
    if (input_json_.empty()) {
        throw std::runtime_error("Function checker: There is no input data in JSON format!");
    }

    if (!input_json_.contains("arg1") && input_json_["arg1"].empty()) {
        throw std::runtime_error("Function checker: The first argument is missing!");
    }

    first_argument_ = input_json_.at("arg1").get<double>();

    if (!input_json_.contains("operation") && input_json_["operation"].empty() &&
        input_json_["operation"].size() > 1) {
        throw std::runtime_error("Function checker: The operation is missing!");
    }

    operation_ = input_json_.at("operation").get<std::string>();

    if (operation_ != "!" && !input_json_.contains("arg2") && input_json_["arg2"].empty()) {
        throw std::runtime_error("Function checker: The second argument is missing!");
    }

    if (operation_ != "!") {
        second_argument_ = input_json_.at("arg2").get<double>();
    }

    // На ноль делить нельзя
    if (operation_ == "/" && second_argument_ == 0.0) {
        throw std::runtime_error("Function checker: You can't divided by zero!");
    }

    Logger::instance().info("The data verification was successful");
}

void CalculatorManager::calculate() {
    switch (operation_[0]) {
    case '+':
        result_ = Library_Math::sum(first_argument_, second_argument_);
        break;
    case '-':
        result_ = Library_Math::minus(first_argument_, second_argument_);
        break;
    case '*':
        result_ = Library_Math::multiplication(first_argument_, second_argument_);
        break;
    case '/':
        result_ = Library_Math::division(first_argument_, second_argument_);
        break;
    case '^':
        result_ = Library_Math::exponentiation(first_argument_, second_argument_);
        break;
    case '!':
        result_ = Library_Math::factorial(static_cast<int>(first_argument_));
        break;
    default:
        throw std::runtime_error(
            "Function calculator: There is no such operation. Select another operation!");
    }

    Logger::instance().info("The calculation was successful");
}

void CalculatorManager::print_result() const {
    std::cout << "Result: " + std::to_string(result_) << "\n";
}

void CalculatorManager::print_help(const char *progName) const {
    std::cout << "Calculator CLI Utility — Help\n\n";
    std::cout << "Usage:\n";
    std::cout << "  " << progName << " --in { \"arg1\": 20, \"operation\": \"/\", \"arg2\": 30 }\n";
    std::cout << "  " << progName << " -i { \"arg1\": 20, \"operation\": \"!\" }\n";
    std::cout << "  " << progName << " --help | -h\n\n";

    std::cout << "Description:\n";
    std::cout << "  A simple command-line calculator that performs:\n";
    std::cout << "    +   addition\n";
    std::cout << "    -   subtraction\n";
    std::cout << "    *   multiplication\n";
    std::cout << "    /   division (checks for divide by zero)\n";
    std::cout << "    ^   power (iterative implementation)\n";
    std::cout << "    !   factorial (recursive implementation)\n\n";

    std::cout << "Examples:\n";
    std::cout << "  " << progName
              << " --in \t{ \"arg1\": 3, \"operation\": \"+\", \"arg2\": 5 }       \t-> Result: 8\n";
    std::cout << "  " << progName
              << " --in \t{ \"arg1\": 3, \"operation\": \"-\", \"arg2\": 5 }       \t-> Result: 5\n";
    std::cout << "  " << progName
              << " --in \t{ \"arg1\": 20, \"operation\": \"*\", \"arg2\": 2 }      \t-> Result: 40\n";
    std::cout << "  " << progName
              << " --in \t{ \"arg1\": 10, \"operation\": \"/\", \"arg2\": 2 }      \t-> Result: 5\n";
    std::cout << "  " << progName
              << " --in \t{ \"arg1\": 2, \"operation\": \"^\", \"arg2\": 2 }       \t-> Result: 4\n";
    std::cout << "  " << progName
              << " --in \t{ \"arg1\": 5, \"operation\": \"!\"}                     \t-> Result: 120\n\n";

    std::cout << "Options:\n";
    std::cout << "  -h, --help    Show this help message and exit\n";
}