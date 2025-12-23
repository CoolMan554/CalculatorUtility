#include <iostream>
#include <string>

#include "math.h"

using namespace std;

void print_help(const char* progName)
{    
    cout << "Calculator CLI Utility — Help\n\n";
    cout << "Usage:\n";
    cout << "  " << progName << " <number1> <operation> <number2>\n";
    cout << "  " << progName << " <number> <operation>\n";
    cout << "  " << progName << " --help | -h\n\n";

    cout << "Description:\n";
    cout << "  A simple command-line calculator that performs:\n";
    cout << "    +   addition\n";
    cout << "    -   subtraction\n";
    cout << "    \\*, '*' , ""*""  multiplication\n";
    cout << "    /   division (checks for divide by zero)\n";
    cout << "    ^   power (iterative implementation)\n";
    cout << "    !   factorial (recursive implementation)\n\n";

    cout << "Examples:\n";
    cout << "  " << progName << " 3 + 5       \t-> Result: 8\n";
    cout << "  " << progName << " 8 - 3       \t-> Result: 5\n";
    cout << "  " << progName << " 20 \\* 2    \t-> Result: 40\n";
    cout << "  " << progName << " 10 / 2      \t-> Result: 5\n";
    cout << "  " << progName << " 2 ^ 8       \t-> Result: 256\n";
    cout << "  " << progName << " 5 !         \t-> Result: 120\n\n";

    cout << "Options:\n";
    cout << "  -h, --help    Show this help message and exit\n";
}

int main(int argc, char** argv)
{
    try
    {
        if(argc < 2)
        {
            std::cout << "There are not enough arguments to get the result! For more information, enter --help" << std::endl;
            return 1;
        }

        if(argc == 2 && (string(argv[1]) == "--help" || string(argv[1]) == "-h"))
        {
            print_help(argv[0]);
            return 0;
        }

        //Если больше 4-х аргументов, то не обрабатываем
        if(argc > 4)
        {
            std::cout << "There are not enough arguments to get the result!" << std::endl;
            return 1;
        }

        double result = 0.0;

        double num1 = std::stod(argv[1]);
        const char *operation = argv[2];
        double num2 = 0.0;

        //Для факториала не вычисляем второе число
        if(*operation != '!')
            num2 = std::stod(argv[3]);

        //На ноль делить нельзя
        if(*operation == '/' && num2 == 0.0)
        {
            std::cout << "You can't divided by zero!" << std::endl;
            return 1;
        }

        switch(*operation)
        {
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
                result = library_math::factorial(num1);
            break;
            default:
                std::cout << "There is no such operation. Select another operation!" << std::endl;
                return 1;

        }

        std::cout << "Result: " << result << std::endl;
    }
    catch(const std::exception &ex)
    {
        std::cout << "Error: " << ex.what();
    }
}