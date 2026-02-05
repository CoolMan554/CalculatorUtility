#include <fstream>

#include "CalculatorManager.h"
#include "library_math.h"

CalculatorManager::CalculatorManager(){

}

void CalculatorManager::runner(int argc, char **argv)
{
    parser(argc, argv);

    checker();

    calculator();

    printer();
}

void CalculatorManager::parser(int argc, char **argv)
{
    int opt;

    while ((opt = getopt_long(argc, argv, "hi:", long_opts, nullptr)) != -1) {
        switch (opt) {
        case 'h':
            print_help(argv[0]);
            help_check = true;
            break;
        case 'i':
            if (optarg != nullptr) {
                std::string json_str = optarg;
                j_parser = json::parse(json_str);
            }
            break;
        case '?':
            throw std::runtime_error("The argument value is missing!");
            break;
        default:
            throw std::runtime_error("There is no such operation!");            
        }
    }
}

void CalculatorManager::checker()
{
    if(help_check)
        exit(0);

    if (j_parser.empty()) {
        throw std::runtime_error("There is no input data in JSON format!");
    }

    if (!j_parser.contains("arg1") && j_parser["arg1"].empty()) {
        throw std::runtime_error("The first argument is missing!");
    }

    first_arg = j_parser.at("arg1").get<double>();

    if (!j_parser.contains("operation") && j_parser["operation"].empty() && j_parser["operation"].size() > 1) {
        throw std::runtime_error("The operation is missing!");     
    }

    operation = j_parser.at("operation").get<string>();

    if (operation != "!" && !j_parser.contains("arg2") && j_parser["arg2"].empty()) {
        throw std::runtime_error("The second argument is missing!");
    }

    if (operation != "!") {
        second_arg = j_parser.at("arg2").get<double>();
    }

    // На ноль делить нельзя
    if (operation == "/" && second_arg == 0.0) {
        throw std::runtime_error("You can't divided by zero!");        
    }
}

void CalculatorManager::calculator()
{
    switch (operation[0]) {
    case '+':
        result = library_math::sum(first_arg, second_arg);
        break;
    case '-':
        result = library_math::minus(first_arg, second_arg);
        break;
    case '*':
        result = library_math::multiplication(first_arg, second_arg);
        break;
    case '/':
        result = library_math::division(first_arg, second_arg);
        break;
    case '^':
        result = library_math::exponentiation(first_arg, second_arg);
        break;
    case '!':
        result = library_math::factorial(static_cast<int>(first_arg));
        break;
    default:
        throw std::runtime_error("There is no such operation. Select another operation!");
    }
}

void CalculatorManager::printer() const
{
    std::cout << "Result: " << result << "\n";
}

void CalculatorManager::print_help(const char *progName) const
{
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