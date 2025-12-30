#include <cstring>
#include <getopt.h>
#include <iostream>
#include <string>

#include "library_math.h"

using namespace std;

struct CalculateInfo {
    std::string first_arg;
    std::string operation;
    std::string second_arg;
    bool help_check = false;
};

// NOLINTNEXTLINE(modernize-avoid-c-arrays)
static option long_opts[] = {{"help", no_argument, nullptr, 'h'},
                             {"arg1", required_argument, nullptr, 'a'},
                             {"arg2", optional_argument, nullptr, 'b'},
                             {"operation", required_argument, nullptr, 'o'}};

void print_help(const char *progName) {
    cout << "Calculator CLI Utility — Help\n\n";
    cout << "Usage:\n";
    cout << "  " << progName << " -a20 -o/ -b30\n";
    cout << "  " << progName << " --arg1=20 --operation=/ --arg2=30\n";
    cout << "  " << progName << " --arg1=20 --operation=! \n";
    cout << "  " << progName << " --help | -h\n\n";

    cout << "Description:\n";
    cout << "  A simple command-line calculator that performs:\n";
    cout << "    +   addition\n";
    cout << "    -   subtraction\n";
    cout << "    *   multiplication\n";
    cout << "    /   division (checks for divide by zero)\n";
    cout << "    ^   power (iterative implementation)\n";
    cout << "    !   factorial (recursive implementation)\n\n";

    cout << "Examples:\n";
    cout << "  " << progName << " \t--arg1=3 \t--operation=+ \t--arg2=5       \t-> Result: 8\n";
    cout << "  " << progName << " \t--arg1=8 \t--operation=- \t--arg2=3       \t-> Result: 5\n";
    cout << "  " << progName << " \t--arg1=20 \t--operation=* \t--arg2=2      \t-> Result: 40\n";
    cout << "  " << progName << " \t--arg1=10 \t--operation=/ \t--arg2=2      \t-> Result: 5\n";
    cout << "  " << progName << " \t--arg1=2 \t--operation=^ \t--arg2=8       \t-> Result: 256\n";
    cout << "  " << progName << " \t--arg1=5 \t--operation=!                  \t-> Result: 120\n\n";

    cout << "Options:\n";
    cout << "  -h, --help    Show this help message and exit\n";
}

CalculateInfo parsing(int argc, char **argv) {
    CalculateInfo info;

    int opt;

    while ((opt = getopt_long(argc, argv, "ha:b:o:", long_opts, nullptr)) != -1) {
        switch (opt) {
        case 'h':
            print_help(argv[0]);
            info.help_check = true;
            break;
        case 'a':
            if (optarg != nullptr) {
                info.first_arg = optarg;
            }
            break;
        case 'o':
            if (optarg != nullptr) {
                info.operation = optarg;
            }
            break;
        case 'b':
            if (optarg != nullptr) {
                info.second_arg = optarg;
            }
            break;
        case '?':
            std::cout << "The argument value is missing!" << "\n";
            break;
        default:
            std::cout << "There is no such operation!" << "\n";
        }
    }

    return info;
}

int checker(const CalculateInfo &info, std::string &error) {
    if (info.first_arg.empty()) {
        error = "The first argument is missing!";
        return -1;
    }

    if (info.operation.empty()) {
        error = "The operation is missing!";
        return -1;
    }

    if (info.operation.size() != 1) {
        error = "Operation must be a single character!";
        return -1;
    }

    if (info.operation != "!" && info.second_arg.empty()) {
        error = "The second argument is missing!";
        return -1;
    }

    // На ноль делить нельзя
    if (info.operation == "/" && info.second_arg == "0") {
        error = "You can't divided by zero!";
        return -1;
    }

    return 0;
}

double calculate(const CalculateInfo &info, std::string &error) {
    double result = 0.0;
    double num1 = std::stod(info.first_arg);
    char operation = info.operation[0];
    double num2 = 0.0;
    if (info.operation != "!") {
        num2 = std::stod(info.second_arg);
    }

    switch (operation) {
    case '+':
        result = library_math::sum(num1, num2);
        break;
    case '-':
        result = library_math::minus(num1, num2);
        break;
    case '*':
        result = library_math::multiplication(num1, num2);
        break;
    case '/':
        result = library_math::division(num1, num2);
        break;
    case '^':
        result = library_math::exponentiation(num1, num2);
        break;
    case '!':
        result = library_math::factorial(static_cast<int>(num1));
        break;
    default:
        error = "There is no such operation. Select another operation!";
    }

    return result;
}

void print(double result) {
    std::cout << "Result: " << result << "\n";
}

int main(int argc, char **argv) {

    CalculateInfo info = parsing(argc, argv);

    if (info.help_check) {
        return 0;
    }

    std::string error_msg;

    if (checker(info, error_msg) == -1) {
        std::cout << error_msg << "\n";
        return -1;
    }

    double result = calculate(info, error_msg);

    if (!error_msg.empty()) {
        std::cout << error_msg << "\n";
        return -1;
    }

    print(result);
}