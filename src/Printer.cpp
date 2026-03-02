#include "Printer.h"
#include <iostream>

void Printer::print(const CalculationRequest &req) {
    if (req.operation == '!')
        std::cout << req.first_argument << " " << req.operation << " = " << req.result << "\n";
    else {
        std::cout << req.first_argument << " " << req.operation << " " << req.second_argument
                  << " = " << req.result << "\n";
    }
}

void Printer::print_help(const std::string &progName) {
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
    std::cout
        << "  " << progName
        << " --in \t{ \"arg1\": 3, \"operation\": \"+\", \"arg2\": 5 }       \t-> Result: 8\n";
    std::cout
        << "  " << progName
        << " --in \t{ \"arg1\": 3, \"operation\": \"-\", \"arg2\": 5 }       \t-> Result: 5\n";
    std::cout
        << "  " << progName
        << " --in \t{ \"arg1\": 20, \"operation\": \"*\", \"arg2\": 2 }      \t-> Result: 40\n";
    std::cout
        << "  " << progName
        << " --in \t{ \"arg1\": 10, \"operation\": \"/\", \"arg2\": 2 }      \t-> Result: 5\n";
    std::cout
        << "  " << progName
        << " --in \t{ \"arg1\": 2, \"operation\": \"^\", \"arg2\": 2 }       \t-> Result: 4\n";
    std::cout
        << "  " << progName
        << " --in \t{ \"arg1\": 5, \"operation\": \"!\"}                     \t-> Result: 120\n\n";

    std::cout << "Options:\n";
    std::cout << "  -h, --help    Show this help message and exit\n";
}