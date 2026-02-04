#include "CalculatorManager.h"
#include "library_math.h"

CalculatorManager::CalculatorManager(){

}

void CalculatorManager::runner(int argc, char **argv)
{
    parser(argc, argv);

    if(help_check)
        return;

    checker();
    calculator();
    printer();
}

void CalculatorManager::parser(int argc, char **argv)
{
    int opt;

    while ((opt = getopt_long(argc, argv, "ha:b:o:", long_opts, nullptr)) != -1) {
        switch (opt) {
        case 'h':
            print_help(argv[0]);
            help_check = true;
            break;
        case 'a':
            if (optarg != nullptr) {
                first_arg = optarg;
            }
            break;
        case 'o':
            if (optarg != nullptr) {
                operation = optarg;
            }
            break;
        case 'b':
            if (optarg != nullptr) {
                second_arg = optarg;
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
    if (first_arg.empty()) {
        throw std::runtime_error("The first argument is missing!");        
    }

    if (operation.empty()) {
        throw std::runtime_error("The operation is missing!");    
    }

    if (operation.size() != 1) {
        throw std::runtime_error("Operation must be a single character!");
    }

    if (operation != "!" && second_arg.empty()) {
        throw std::runtime_error("The second argument is missing!");
    }

    // На ноль делить нельзя
    if (operation == "/" && second_arg == "0") {
        throw std::runtime_error("You can't divided by zero!");        
    }
}

void CalculatorManager::calculator()
{
    double num1 = std::stod(first_arg);
    char operation_new = this->operation[0];
    double num2 = 0.0;
    if (operation_new != '!') {
        num2 = std::stod(second_arg);
    }

    switch (operation_new) {
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
        throw std::runtime_error("There is no such operation. Select another operation!");
    }
}

void CalculatorManager::printer() const
{
    std::cout << "Result: " << result << "\n";
}